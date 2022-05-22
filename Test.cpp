#include "sources/OrgChart.hpp"
#include "doctest.h"

using namespace std;
using namespace ariel;

TEST_CASE("Main test include all functions"){
    OrgChart tempChart;
    //adding root node and sun nodes
    tempChart.add_root("A");
    tempChart.add_sub("A","B");
    tempChart.add_sub("A","C");
    tempChart.add_sub("A","D");
    tempChart.add_sub("B","b");
    tempChart.add_sub("C","c");
    tempChart.add_sub("D","d");
    /*
    should look somthing like this
    A
    |
    B--------C--------D
    |        |        |
    b--------c--------d
    */

   //Check  iter_begin_level_order,  iter_begin_reverse_order,  iter_begin_preorder
   CHECK_EQ(tempChart.begin_level_order().getNodes().at(0)->title,"A");
   CHECK_EQ(tempChart.begin_level_order().getNodes().at(0)->title,"b");
   CHECK_EQ(tempChart.begin_level_order().getNodes().at(0)->title,"A");

   //check getNodes return all nodes
   CHECK_EQ(tempChart.begin_level_order().getNodes().size(),7);
   CHECK_EQ(tempChart.begin_level_order().getNodes().size(),7);
   CHECK_EQ(tempChart.begin_level_order().getNodes().size(),7);

   //checking all printing methods, creating vectors to all methods
   //begin level order
   vector<string> begin_vector = {"A","B","C","D","b","c","d"};
      
   //reverse level order
   vector<string> reverse_vector = {"b","c","d","B","C","D","A"};

   //pre order
   vector<string> preVector = {"A","B","b","C","c","D","d"};

   //LOOPS FOR CHECKING THE PRINTS
   unsigned int i=0;
   // Check begin level order
   for(auto it=tempChart.begin_level_order(); it != tempChart.end_level_order(); ++it){
       CHECK_EQ(*it,begin_vector.at(i));
   }

   // Check reverse level order
    for(auto it=tempChart.begin_reverse_order(); it != tempChart.reverse_order(); ++it){
       CHECK_EQ(*it,reverse_vector.at(i));
   }
   // Check pre order
    for(auto it=tempChart.begin_preorder(); it != tempChart.end_preorder(); ++it){
       CHECK_EQ(*it,preVector.at(i));
   }

   //check replacing root
   CHECK_EQ(tempChart.begin_level_order().getNodes().at(0)->title,"A");
   tempChart.add_root("NewRoot");
   CHECK_EQ(tempChart.begin_level_order().getNodes().at(0)->title,"NewRoot");

   //check throw for adding sun with no actual parent
   CHECK_THROWS(tempChart.add_sub("G","B"));
   CHECK_THROWS(tempChart.add_sub("g","B"));

   //check throw for adding root with no name!
   CHECK_THROWS(tempChart.add_root(""));

   //check throw for adding sub to root with no name!
   CHECK_THROWS(tempChart.add_sub("A",""));

   //check throw for adding sub to other sub with no name!
   CHECK_THROWS(tempChart.add_sub("b",""));

   //adding new nodes with same title should be ok!
   CHECK_NOTHROW(tempChart.add_sub("B","B"));
   CHECK_NOTHROW(tempChart.add_sub("A","B")); // allready exist should not interupt
   CHECK_NOTHROW(tempChart.add_sub("b","B"));
   CHECK_NOTHROW(tempChart.add_sub("c","A")); //allready exist as root should not interupt
   CHECK_NOTHROW(tempChart.add_sub("A","c")); // LOOK LIKE MAKING A LOOP , BUT ITS NEW NODE!

}