package test;
import java.util.Arrays;
import java.util.Random;

public class URLHelpers {

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
    public static String randomValidHost(int maxDomainLength, int numberOfDomains) {
        String host = "";
        Random rand = new Random();

        for (int domainNum = 0; domainNum < numberOfDomains; domainNum++) {
            int randomNum = rand.nextInt(51);
            if (randomNum < 26) host += (char)(randomNum + 'a');
            else host += (char)((randomNum - 26) + 'A');

            int domainSize = rand.nextInt(maxDomainLength);
            for (int domainChar = 0; domainChar < domainSize; domainChar++) {
                randomNum = rand.nextInt(62);
                if (randomNum < 26) host += (char)(randomNum + 'a');
                else if (randomNum < 52) host += (char)((randomNum-26) + 'A');
                else if (randomNum < 62) host += (char)((randomNum-52) + '0');
                else host += '-';
            }

            host += '.';
        }

        // Add top level domain
        int randomNum = rand.nextInt(TLDs.topLevelDomains.length - 1);
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