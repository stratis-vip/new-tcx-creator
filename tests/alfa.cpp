#include "suit.hpp"
#include "bignums.hpp"

int main (int argc, char * argv[])
{



// TEST(isNumeric, IsZeroStringWthitDots) {
//   ASSERT_THAT(isNumeric("000.00"), Eq(true));
// }
    suit::addT("isNumeric", "isNumeric(\"\") Πρέπει να έχει μηδενικό μήκος", isNumeric(""), TestTypes::equal, false);
    suit::addT("isNumeric", "Χαρακτήρες με μηδενικά είναι δεκτοί", isNumeric("0000"), TestTypes::equal, true);
    suit::addT("isNumeric", "Χαρακτήρες με μείον είναι δεκτοί", isNumeric("-00001"), TestTypes::equal, true);
    suit::addT("isNumeric", "Χαρακτήρες με μείον είναι δεκτοί", isNumeric("-0000"), TestTypes::equal, true);
    suit::addT("isNumeric", "Χαρακτήρες με μηδέν και μια υποδιαστολή", isNumeric("000.00"), TestTypes::equal, true);
    suit::addT("isNumeric", "Χαρακτήρες με μείον και μια υποδιαστολή", isNumeric("0010.00"), TestTypes::equal, true);
    suit::addT("isNumeric", "Χαρακτήρες με κενά δεν είναι δεκτοί", isNumeric("0 00 00"), TestTypes::equal, false);
    suit::addT("isNumeric", "Ξεκινά με υποδιαστολή", isNumeric(".001"), TestTypes::equal, true);
    suit::addT("isNumeric", "Ξεκινά με δυο υποδιαστολές", isNumeric("..001"), TestTypes::equal, false);
    suit::addT("isNumeric", "Ξεκινά και τελειώνει με υποδιαστολές", isNumeric(".001.."), TestTypes::equal, false);

    
    

    return suit::runTests(argc, argv);
}