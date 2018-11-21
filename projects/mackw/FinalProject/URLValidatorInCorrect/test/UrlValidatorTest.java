package test;


import junit.framework.TestCase;
import src.UrlValidator;
import java.util.Random;



public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   public void customAssert(String statement, boolean boolOne, boolean boolTwo)
   {
      String assertionError = null;
      try {
         assertEquals(boolOne,boolTwo);
      }
      catch (AssertionError ae) {
         assertionError = ae.toString();
      }

      if(assertionError != null)
         System.out.printf("%s %s %n", statement, assertionError);
   }
   
   
   public void testManualTest()
   {
	   System.out.println("Manual Test....");
	   
	   String[] trueURLsTwoSlash = {
	              "http://localhost/", // Typical with slash
	              "http://machine/", // local address
	              "http://localhost:8000", // with ports
	              "ftp://localhost:8000",
	              "http://machine:0",
	              "http://www.google.com/test//testfile",
	              "ftp://www.google.com/test//testfile",
	              "ftp://www.google.com/file1//test2//test3"
	      };

	      // Insert the manual URls that we are going to test
	      String[] trueURLS = {"http://www.google.com", //valid url
	              "http://www.google.com/", // valid with slash
	              "http://0.0.0.0/", // local address
	              "http://www.google.com/test", // path
	              "http://stackoverflow.com/", // No Domain
	              "http://www.google.com/test/test/test/test/test/test/testFile", // long path
	              "http://www.google.com/test?action=view", // query
	              "http://www.google.com/#/",// path with symbol
	              "http://www.google.com/23/", // path with number
	              "http://www.google.ceo", // different TLD
	              "http://www.google.food",
	              "http://www.google.com:0", // ports
	              "http://www.google.com:6000"
	      };

	      // List all false URLs
	      String[] falseURLS = {"http://www.google.cmx/", // bad TLD
	              "http://www.google.aaab", // bad TLD
	              "http://www.google.jdifj", // bad TLD case
	              "ftp://www.google.jdifj", // bad TLD cases

	              "htp:/www.google.com/", // Incorrect Scheme Variations
	              "http:/www.google.com/",
	              "http:/www.google.com/#", //address with incorrect path option",
	              "255.255.255.255", // no Scheme
	              "http://256.256.256.256", // Impossible IP address
	              "ftp://256.256.256.256",
	              "http://www.google.com/..//file", // dots in file
	              "http://www.google.com:-1", // bad Port
	              "http://www.google.com:65a",
	              "http://www.google.com/test//testfile", // try two slashes
	              "http://localhost/", // Typical with slash
	              "http://machine/", // local address
	              "http://localhost:8000", // with ports
	              "ftp://localhost:8000",
	              "http://machine:0",
	              "http://www.google.com/test//testfile",
	              "ftp://www.google.com/test//testfile",
	              "ftp://www.google.com/file1//test2//test3"
	      };
	   
	      // setup default UrlValudator with "http,https,ftp" as valid schemes
	      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_2_SLASHES);
	   
	   	  // Run through the true URLs
	      for(int i = 0; i < trueURLS.length; i++)
	      {
	         customAssert(trueURLS[i], true, urlVal.isValid(trueURLS[i]));
	      }

	      // Run through the false URLs
	      for(int i = 0; i < falseURLS.length; i++)
	      {
	         customAssert(falseURLS[i], false, urlVal.isValid(falseURLS[i]));
	      }
	     
	      
   }
   
   
   public void testYourFirstPartition()
   {
	  //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		//You can use this function to implement your Second Partition testing	   

   }
   
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES );
      Random rand = new Random();

      for (int i = 0; i < 10; i++) {
         // set random scheme
         //String URL = URLHelpers.randomValidScheme(5);
         // lets start with just http
         String URL = "http://";

         // Generate random authority
         URL += URLHelpers.randomValidHost(rand.nextInt(20)+1);


         // Generate random port number
         URL += ":" + URLHelpers.randomValidPortNumber();
         

         // Generate random valid path with 0,1 or 2 segment
         URL += URLHelpers.randomValidPath(rand.nextInt(10)+2, rand.nextInt(3));


         // Generate random valid query
         URL += URLHelpers.randomValidQuery(rand.nextInt(30));

         // print URL
         System.out.printf("URL # %d: %s %n",i + 1, URL);

         
         try {
        	 // get expected value from URLHelpers
             boolean expected = URLHelpers.isURLValid(URL);
             // test URL using URLValidator
             boolean actual = urlVal.isValid(URL);
             // check results match
             customAssert(URL, expected, actual);
             //if (expected != actual) deltaDebug(URL);
          } catch (Exception e) {
             //e.printStackTrace();
             System.out.printf("Caused exception: %s %n",URL);
          }
   }
   


   }
}
