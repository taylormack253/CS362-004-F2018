package test;
import java.util.Arrays;
import java.util.Random;

public class URLHelpers {
	
   public static boolean isURLValid(String url) {
       // Must contain :// after scheme
       if (!url.contains("://")) return false;

       // # is the end of the URL. Don't check anything after it
       if (url.contains("#")) {
           url = url.substring(0, url.indexOf('#'));
       }

       // Check scheme before ://
       String scheme = url.substring(0, url.indexOf("://"));
       if (!isSchemeValid(scheme)) return false;

       url = url.substring(url.indexOf("://")+3);

       // Check authority (before / or ?)
       String authority = url;
       if (authority.contains("?")) {
           authority = authority.substring(0, authority.indexOf("?"));
       }
       if (authority.contains("/")) authority = authority.substring(0, authority.indexOf("/"));
       if (!isAuthorityValid(authority)) return false;

       // Check path if it exists
       // For path to exist, there must be a "/" before any "?"
       int pathStartIndex, pathEndIndex;
       if (url.contains("/")) {
           if (url.contains("?")) {
               if (url.indexOf("/") < url.indexOf("?")) {
                   pathStartIndex = url.indexOf("/");
                   pathEndIndex = url.indexOf("?");
               } else { // No path, ? before /
                   pathStartIndex = 0;
                   pathEndIndex = 0;
               }
           } else { // No ?, so the rest of the url is the path
               pathStartIndex = url.indexOf("/");
               pathEndIndex = url.length();
           }
       } else { // No /, no path
           pathStartIndex = 0;
           pathEndIndex = 0;
       }
       String path = url.substring(pathStartIndex, pathEndIndex);
       if (!isPathValid(path)) return false;

       // Validate query if there is one
       if (url.contains("?")) {
           String query = url.substring(url.indexOf("?"));
           if (!isQueryValid(query)) return false;
       }

       // Else URL is valid
       return true;
   }

   /*
       Checks that a given scheme is valid
    */
   public static boolean isSchemeValid(String scheme) {
       // Must have length at least 1
       if (scheme.length() == 0) return false;

       // Must begin with a letter
       if (!Character.isLetter(scheme.charAt(0))) return false;

       // Every character must be a letter, number, +, -, or .
       // according to RFC2396 Appendix A
       for (int strIndex = 1; strIndex < scheme.length(); strIndex++) {
           if (!(
                   Character.isLetter(scheme.charAt(strIndex)) ||
                           Character.isDigit(scheme.charAt(strIndex)) ||
                           scheme.charAt(strIndex) == '+' ||
                           scheme.charAt(strIndex) == '-' ||
                           scheme.charAt(strIndex) == '.')) {
               return false;
           }
       }

       // Else it is a valid scheme
       return true;
   }

   /*
       Checks that a given authority is valid. Can be a host name
       or IPv4 address
    */
   public static boolean isAuthorityValid(String authority) {
       if (isIPValid(authority)) return true;
       else if (isHostValid(authority)) return true;
       else return false;
   }

   /*
       Checks if a given string is a valid IPv4 address
    */
   public static boolean isIPValid(String ip) {

       // If it has a port, check that first
       if (ip.contains(":")) {
           String port = ip.substring(ip.indexOf(":")+1);
           if (!isPortValid(port)) return false;

           ip = ip.substring(0, ip.indexOf(":"));
       }

       int bytes[] = {-1, -1, -1, -1}; // The 4 bytes that make up IP address
       try {
           // 3 times, parse out a number and cut off everything through the period
           for (int i = 0; i < 3; i++) {
               bytes[i] = Integer.parseInt(ip.substring(0, ip.indexOf(".")));
               ip = ip.substring(ip.indexOf(".")+1);
           }
           // last time, just parse the remaining number
           bytes[3] = Integer.parseInt(ip);
       } catch (Exception e) {
           // Any exception in parsing or substings means it was not valid
           return false;
       }

       // Each byte must not exceed the size of 1 byte
       for (int i = 0; i < 4; i ++) {
           if (bytes[i] < 0 || bytes[i] > 255) return false;
       }

       // Else IP is valid
       return true;
   }

   /*
       Checks that a given string can be a valid host name. Checks the top level domain against a list of registered TLDs
    */
   public static boolean isHostValid(String host) {
       // First check the port if there is one
       if (host.contains(":")) {
           String port = host.substring(host.indexOf(":")+1);
           if (!isPortValid(port)) return false;

           host = host.substring(0, host.indexOf(":"));
       }

       // Cut off . at the end
       if (host.length() >= 1) {
           if (host.charAt(host.length() - 1) == '.') host = host.substring(0, host.length() - 1);
       }

       // If it is a local TDL, it is exempt from the rules below
       if (host.equalsIgnoreCase("localhost") || host.equalsIgnoreCase("localdomain")) return true;

       // There must be a top level domain and at least one lower level domain, separated by "."
       // Domains must start with a letter or number and can have "-" in the middle
       // Top level domains must belong to a list of existing TLD's

       // Must contain "."
       if (!host.contains(".")) return false;

       while (host.contains(".")) {
           String domain = host.substring(0,host.indexOf("."));
           host = host.substring(host.indexOf(".")+1);

           // domain must have at least 1 character
           if (domain.length() == 0) return false;

           // Each character must be alphanum or "-". First and last cannot be "-"
           if (domain.charAt(0) == '-' || domain.charAt(domain.length()-1) == '-') return false;

           for (int strIndex = 0; strIndex < domain.length(); strIndex++) {
               if (!(
                       Character.isLetter(domain.charAt(strIndex)) ||
                               Character.isDigit(domain.charAt(strIndex)) ||
                               domain.charAt(strIndex) == '-')) {
                   return false;
               }
           }
       }

       // Top level domain must belong to the list of existing top level domains
       // DNS is case insensitive
       host = host.toLowerCase();
       if (Arrays.binarySearch(TLDs.topLevelDomains, host) < 0) return false;

       return true;
   }

   /*
       Checks that a given port number is valid (between 0 and 65535)
    */
   public static boolean isPortValid(String port) {
       // if port is blank, it is accepted
       if (port.length() == 0) return true;

       int portNum = -1;
       // Port must be an integer
       try {
           portNum = Integer.parseInt(port);
       } catch (NumberFormatException e) {
           return false;
       }

       // Must be between 0 and 65535
       if (portNum < 0 || portNum > 65535) return false;

       // Else it is a valid port
       return true;
   }

   /*
       Checks the characters in a string to see if it can be a URL path
    */
   public static boolean isPathValid(String path) {
       // If there is a path, it has to start with a slash (/)
       if (path.length() > 0) {
           if (path.charAt(0) != '/') return false;
       }

       // Every character in the path must belong to the list below
       // Unreserved, escaped (%), or ":", "@", "&", "=", "+", "$", ",", ";"
       for (int strIndex = 0; strIndex < path.length(); strIndex++) {
           if (!(
                   Character.isLetter(path.charAt(strIndex)) ||
                           Character.isDigit(path.charAt(strIndex)) ||
                           path.charAt(strIndex) == '-' ||
                           path.charAt(strIndex) == '_' ||
                           path.charAt(strIndex) == '.' ||
                           path.charAt(strIndex) == '!' ||
                           path.charAt(strIndex) == '~' ||
                           path.charAt(strIndex) == '*' ||
                           path.charAt(strIndex) == '\'' ||
                           path.charAt(strIndex) == '(' ||
                           path.charAt(strIndex) == ')' ||
                           path.charAt(strIndex) == '%' ||
                           path.charAt(strIndex) == ':' ||
                           path.charAt(strIndex) == '@' ||
                           path.charAt(strIndex) == '&' ||
                           path.charAt(strIndex) == '=' ||
                           path.charAt(strIndex) == '+' ||
                           path.charAt(strIndex) == '$' ||
                           path.charAt(strIndex) == ',' ||
                           path.charAt(strIndex) == ';' ||
                           path.charAt(strIndex) == '/')) {
               return false;
           }

           // No consecutive slash or period
           if (path.charAt(strIndex) == '/' && path.length() > strIndex+1) {
               if (path.charAt(strIndex + 1) == '/') return false;
           }
           if (path.charAt(strIndex) == '.' && path.length() > strIndex+1) {
               if (path.charAt(strIndex + 1) == '.') return false;
           }
       }

       // Else path is valid
       return true;
   }

   /*
       Checks the characters in a string to see if it can be a URL query
    */
   public static boolean isQueryValid(String query) {
       // Query must start with ?
       if (query.length() > 0) {
           if (query.charAt(0) != '?') return false;
       }

       // Characters before pound sign must not be whitespace
       // Characters after pound sign can be whitespace
       for (int strIndex = 0; strIndex < query.length(); strIndex++) {
           if (Character.isWhitespace(query.charAt(strIndex))) return false;
       }

       // Else query is valid
       return true;
   }
    /*
        Methods to generate random URL components
     */

    /*
        Produces a random scheme of given size
     */
    public static String randomValidScheme(int size) {
        Random rand = new Random();
        String scheme = "";

        int randomNum = rand.nextInt(51);
        if (randomNum < 26) scheme += (char)(randomNum + 'a');
        else scheme += (char)((randomNum - 26) + 'A');

        for (int i = 1; i < size; i++) {
            randomNum = rand.nextInt(64);
            if (randomNum < 26) scheme += (char)(randomNum + 'a');
            else if (randomNum < 52) scheme += (char)((randomNum - 26) + 'A');
            else if (randomNum < 62) scheme += Integer.toString(randomNum - 52);
            else if (randomNum == 62) scheme += '-';
            else if (randomNum == 63) scheme += '+';
            else scheme += '.';
        }

        return scheme;
    }

    /*
        Produce a random IPv4 address
     */
    public static String randomValidIP() {
        String ip = "";
        Random rand = new Random();

        ip += Integer.toString(rand.nextInt(255));

        for (int i = 0; i < 3; i++) {
            ip += '.' + Integer.toString(rand.nextInt(255));
        }

        return ip;
    }

    /*
        Produce a random host name
     */
    public static String randomValidHost(int maxDomainLength) {
        String host = "www.";
        Random rand = new Random();

            int randomNum = rand.nextInt(51);
            if (randomNum < 26) host += (char)(randomNum + 'a');
            else host += (char)((randomNum - 26) + 'A');

            int domainSize = rand.nextInt(maxDomainLength);
            for (int domainChar = 0; domainChar < domainSize; domainChar++) {
            randomNum = rand.nextInt(62);
            // lowercase letters
            if (randomNum < 26) host += (char)(randomNum + 'a');
            // uppercase letters
            else if (randomNum < 52) host += (char)((randomNum-26) + 'A');
            // valid symbols
            else if (randomNum < 62) host += (char)((randomNum-52) + '0');
            else host += '-';
         }

         host += '.';
    

        // Add top level domain
        randomNum = rand.nextInt(TLDs.topLevelDomains.length - 1);
        host += TLDs.topLevelDomains[randomNum];

        return host;
    }

    public static String randomValidPortNumber() {
        return randomInteger(0, 65535);
    }

    /*
        Produces a random URL path. Specify the maximum length per segment and the number of segments
     */
    public static String randomValidPath(int maxSegmentLength, int numberOfSegments) {
        String path = "";
        Random rand = new Random();

        for (int segmentNum = 0; segmentNum < numberOfSegments; segmentNum++) {
            path += '/';

            int segmentSize = rand.nextInt(maxSegmentLength-1) + 1;
            for (int segmentChar = 0; segmentChar < segmentSize; segmentChar++) {
                int randomNum = rand.nextInt(80);
                if (randomNum < 26) path += (char)(randomNum + 'a');
                else if (randomNum < 52) path += (char)((randomNum-26) + 'A');
                else if (randomNum < 62) path += (char)((randomNum-52) + '0');
                else if (randomNum == 62) path += '-';
                else if (randomNum == 63) path += '_';
                else if (randomNum == 64) path += '!';
                else if (randomNum == 65) path += '~';
                else if (randomNum == 66) path += '*';
                else if (randomNum == 67) path += '\'';
                else if (randomNum == 68) path += '(';
                else if (randomNum == 69) path += ')';
                else if (randomNum == 70) path += '%';
                else if (randomNum == 71) path += ':';
                else if (randomNum == 72) path += '@';
                else if (randomNum == 73) path += '&';
                else if (randomNum == 74) path += '=';
                else if (randomNum == 75) path += '+';
                else if (randomNum == 76) path += '$';
                else if (randomNum == 77) path += ',';
                else if (randomNum == 78) path += ';';
                else if (randomNum == 79) path += '-';
                else {
                    if (path.charAt(path.length()-1) != '.') path += '.';
                }
            }
        }

        return path;
    }

    /*
        Produces a random URL query of given length
     */
    public static String randomValidQuery(int size) {
        String query = "";
        Random rand = new Random();

        if (size > 0) query += '?';

        for (int i = 1; i < size; i++) {
            int randomNum = rand.nextInt(81);
            if (randomNum < 26) query += (char)(randomNum + 'a');
            else if (randomNum < 52) query += (char)((randomNum-26) + 'A');
            else if (randomNum < 62) query += (char)((randomNum-52) + '0');
            else if (randomNum == 62) query += '-';
            else if (randomNum == 63) query += '_';
            else if (randomNum == 64) query += '!';
            else if (randomNum == 65) query += '~';
            else if (randomNum == 66) query += '*';
            else if (randomNum == 67) query += '\'';
            else if (randomNum == 68) query += '(';
            else if (randomNum == 69) query += ')';
            else if (randomNum == 70) query += '%';
            else if (randomNum == 71) query += ':';
            else if (randomNum == 72) query += '@';
            else if (randomNum == 73) query += '&';
            else if (randomNum == 74) query += '=';
            else if (randomNum == 75) query += '+';
            else if (randomNum == 76) query += '$';
            else if (randomNum == 77) query += ',';
            else if (randomNum == 78) query += ';';
            else if (randomNum == 79) query += '-';
            else if (randomNum == 80) query += '/';
            else query += '?';

        }
        return query;
    }

    /*
        Produces a random string. Not guaranteed to be valid for any part of a URL
     */
    // ASCII characters from " " to "~"
    public static String randomString(int size) {
        String randString = "";
        Random rand = new Random();

        int randomNum;

        for (int i = 0; i < size; i++) {
            randomNum = rand.nextInt(126-32);
            randString += (char)(randomNum + ' ');
        }

        return randString;
    }

    public static String randomInteger(int minimum, int maximum) {
        String randInt = "";
        Random rand = new Random();

        int randomNum = rand.nextInt(maximum-minimum) + minimum;
        randInt = Integer.toString(randomNum);
        return randInt;
    }
}