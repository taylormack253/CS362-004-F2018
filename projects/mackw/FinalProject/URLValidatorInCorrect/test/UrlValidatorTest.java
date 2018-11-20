

import junit.framework.TestCase;



public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
     //You can use this function to implement your manual testing	   
	   
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
         URL += URLHelpers.randomValidHost(rand.nextInt(20)+1, rand.nextInt(5)+1);


         // Generate random port number
         URL += ":" + URLHelpers.randomValidPortNumber();
         

         // Generate random valid path with 0,1 or 2 segment
         URL += URLHelpers.randomValidPath(rand.nextInt(10)+2, rand.nextInt(3));


         // Generate random valid query
         URL += URLHelpers.randomValidQuery(rand.nextInt(30));

         // print URL
         System.out.println(URL);

   }
   


}
