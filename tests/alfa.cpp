#include "suit.hpp"
#include "bignums.hpp"

class TestBnum {
public:
  BigNum bn{"123", "345", true};
};

void fixgetValueFromString(){
  BigNum f{};
  f = getValueFromString("1232212986.034520023");
  suit::addT("isNumeric", "Έλεγχος αρχικής τιμής", f.value().c_str(), TestTypes::equal, "1232212986.034520023");
}

void fixgetValueFromNegativeString(){
  BigNum f{};
  f = getValueFromString("-1232212986.034520023");
  suit::addT("isNumeric", "Έλεγχος αρχικής αρνητικής τιμής", f.value().c_str(), TestTypes::equal, "-1232212986.034520023");
}

int main (int argc, char * argv[])
{
   BigNum f{"123", "345", true};


// TEST(isNumeric, IsZeroStringWthitDots) {
//   ASSERT_THAT(isNumeric("000.00"), Eq(true));
// }
    // suit::addT("isNumeric", "isNumeric(\"\") Πρέπει να έχει μηδενικό μήκος", isNumeric(""), TestTypes::equal, false);
    // suit::addT("isNumeric", "Χαρακτήρες με μηδενικά είναι δεκτοί", isNumeric("0000"), TestTypes::equal, true);
    // suit::addT("isNumeric", "Χαρακτήρες με μείον είναι δεκτοί", isNumeric("-00001"), TestTypes::equal, true);
    // suit::addT("isNumeric", "Χαρακτήρες με μείον είναι δεκτοί", isNumeric("-0000"), TestTypes::equal, true);
    // suit::addT("isNumeric", "Χαρακτήρες με μηδέν και μια υποδιαστολή", isNumeric("000.00"), TestTypes::equal, true);
    // suit::addT("isNumeric", "Χαρακτήρες με μείον και μια υποδιαστολή", isNumeric("0010.00"), TestTypes::equal, true);
    // suit::addT("isNumeric", "Χαρακτήρες με κενά δεν είναι δεκτοί", isNumeric("0 00 00"), TestTypes::equal, false);
    // suit::addT("isNumeric", "Ξεκινά με υποδιαστολή", isNumeric(".001"), TestTypes::equal, true);
    // suit::addT("isNumeric", "Ξεκινά με δυο υποδιαστολές", isNumeric("..001"), TestTypes::equal, false);
    // suit::addT("isNumeric", "Ξεκινά και τελειώνει με υποδιαστολές", isNumeric(".001.."), TestTypes::equal, false);
    // suit::addT("isNumeric", "Έχει χαρακτήρες", isNumeric("001a"), TestTypes::equal, false);
    // suit::addT("isNumeric", "Έχει χαρακτήρες και υποδιαστολή", isNumeric("0.01a"), TestTypes::equal, false);
    // suit::addT("isNumeric", "Έχει κενά και υποδιαστολή", isNumeric("0. 01"), TestTypes::equal, false);
    // suit::addT("isNumeric", "Έλεγχος αρχικών τιμών", f.value().c_str(), TestTypes::equal, "-123.345");
    fixgetValueFromString();
    fixgetValueFromNegativeString();
    return suit::runTests(argc, argv);
}