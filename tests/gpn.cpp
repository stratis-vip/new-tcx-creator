#include "bignums.hpp"
#include "gmock/gmock.h"

using namespace testing;

TEST(isNumeric, IsZeroLength) { ASSERT_THAT(isNumeric(""), Eq(false)); }

TEST(isNumeric, IsZeroString) { ASSERT_THAT(isNumeric("00000"), Eq(true)); }
TEST(isNumeric, IsnegativeString) { ASSERT_THAT(isNumeric("-0"), Eq(true)); }

TEST(isNumeric, IsZeroStringWthitDots) {
  ASSERT_THAT(isNumeric("000.00"), Eq(true));
}

TEST(isNumeric, IsStartingWithDot) { ASSERT_THAT(isNumeric(".001"), Eq(true)); }

TEST(isNumeric, IsStartingWith2Dot) {
  ASSERT_THAT(isNumeric("..001"), Eq(false));
}

TEST(isNumeric, IsEndingWithDot) { ASSERT_THAT(isNumeric("001."), Eq(true)); }

TEST(isNumeric, IsEndingWith2Dot) {
  ASSERT_THAT(isNumeric("001.."), Eq(false));
}

TEST(isNumeric, IsStartingAnedEndingWithDot) {
  ASSERT_THAT(isNumeric(".001.."), Eq(false));
}

TEST(isNumeric, ContainsLetters) { ASSERT_THAT(isNumeric("001a"), Eq(false)); }

TEST(isNumeric, ContainsLettersDots) {
  ASSERT_THAT(isNumeric("0.01a"), Eq(false));
}
TEST(isNumeric, ContainsSpaces) { ASSERT_THAT(isNumeric("0. 01"), Eq(false)); }

class TestBnum : public Test {
public:
  BigNum bn{"123", "345", true};
};

TEST_F(TestBnum, CheckInitValues) { ASSERT_THAT(bn.value(), Eq("-123.345")); }

TEST_F(TestBnum, CheckgetValueFromString) {
  bn = getValueFromString("1232212986.034520023");
  ASSERT_THAT(bn.value(), Eq("1232212986.034520023"));
}

TEST_F(TestBnum, CheckgetValueFromNegativeString) {
  bn = getValueFromString("-1232212986.034520023");
  ASSERT_THAT(bn.value(), Eq("-1232212986.034520023"));
}

TEST_F(TestBnum, CheckgetValueZero) {
  bn = getValueFromString("0");
  ASSERT_THAT(bn.value(), Eq("0.0"));
}

TEST_F(TestBnum, CheckgetValueZeroFromWrong) {
  bn = getValueFromString("0..45");
  ASSERT_THAT(bn.value(), Eq("0.0"));
}

TEST(strToI, ThrowExceptionOnChar) {
  EXPECT_THROW(strToI("a"), std::invalid_argument);
}

TEST(intpow, returns1) { ASSERT_THAT(intPow(10, 0), Eq(1UL)); }
TEST(intpow, returns10) { ASSERT_THAT(intPow(10, 1), Eq(10UL)); }

TEST(strToI, returns4) { ASSERT_THAT(strToI("4"), Eq(4UL)); }

TEST(strToI, returns0) { ASSERT_THAT(strToI("0"), Eq(0UL)); }

TEST(strToI, returns10123) { ASSERT_THAT(strToI("1012"), Eq(1012UL)); }

TEST(strToI, returns101234567) {
  ASSERT_THAT(strToI("101234567"), Eq(101234567UL));
}

TEST(Addition, add0and0) {
  BigNum a{0, 0};
  BigNum b{0, 0};
  ASSERT_THAT((a + b).value(), Eq("0.0"));
}

TEST(Addition, add1and1) {
  BigNum a{1, 0};
  BigNum b{1, 0};
  ASSERT_THAT((a + b).value(), Eq("2.0"));
}

TEST(Addition, add1_1and1_2) {
  BigNum a{1, 1};
  BigNum b{1, 2};
  ASSERT_THAT((a + b).value(), Eq("2.3"));
}

TEST(Addition, add1_1and1_01) {
  BigNum a{1, 1};
  BigNum b{"1", "01"};
  ASSERT_THAT((a + b).value(), Eq("2.11"));
}

TEST(Addition, add1_21and1_01) {
  BigNum a{1, 21};
  BigNum b{"0", "01", true};
  ASSERT_THAT((a + b).value(), Eq("1.20"));
}

TEST(Addition, add1_34and1_81) {
  BigNum a{1, 34};
  BigNum b{"1", "81"};
  ASSERT_THAT((a + b).value(), Eq("3.15"));
}

TEST(Addition, add123_3164and156_8100945) {
  BigNum a{123, 3164};
  BigNum b{"156", "8100945"};
  ASSERT_THAT((a + b).value(), Eq("280.1264945"));
}

TEST(Addition, add1andminus1) {
  BigNum a{1, 1};
  BigNum b{-1, 1};
  ASSERT_THAT((a + b).value(), Eq("0.0"));
}

TEST(Creation, minusInteger) {
  BigNum a{-1, 1};
  BigNum b{-1, 1};
  ASSERT_THAT((a + b).value(), Eq("-2.0"));
}

TEST(trimLeftZero, delete5zeros) {
  ASSERT_THAT(trimLeftZero("00000"), Eq("0"));
}

TEST(trimLeftZero, delete5zerosNegative) {
  ASSERT_THAT(trimLeftZero("-00000"), Eq("-0"));
}

TEST(trimLeftZero, delete5zerosBefore1) {
  ASSERT_THAT(trimLeftZero("000001"), Eq("1"));
}

TEST(trimLeftZero, delete5zerosbefore10) {
  ASSERT_THAT(trimLeftZero("0000010"), Eq("10"));
}

TEST(trimLeftZero, delete5zerosbefore10Negative) {
  ASSERT_THAT(trimLeftZero("-0000010"), Eq("-10"));
}

TEST(trimLeftZero, deleteRandomNumber) {
  ASSERT_THAT(trimLeftZero("-00452343222234147890564346789710"),
              Eq("-452343222234147890564346789710"));
}

TEST(trimLeftZero, ThrowExceptionOnChar) {
  EXPECT_THROW(trimLeftZero("000000a"), std::invalid_argument);
}

TEST(trimRightZero, delete5zeros) {
  ASSERT_THAT(trimRightZero("00000"), Eq("0"));
}

TEST(trimRightZero, deletezerosBefore1) {
  ASSERT_THAT(trimRightZero("100000"), Eq("1"));
}

TEST(trimRightZero, deletezerosBefore10001) {
  ASSERT_THAT(trimRightZero("1000100"), Eq("10001"));
}

TEST(fillRightZero, make10to1000) {
  std::string a{"10"};
  fillRightZero(a, 4);
  ASSERT_THAT(a, Eq("1000"));
}

TEST(fillRightZero, make100to10) {
  std::string a{"100"};
  fillRightZero(a, 1);
  ASSERT_THAT(a, Eq("100"));
}

TEST(fillRightZero, make100to100) {
  std::string a{"100"};
  fillRightZero(a, 2);
  ASSERT_THAT(a, Eq("100"));
}

TEST(fillRightZero, make100to1) {
  std::string a{"100"};
  fillRightZero(a, 0);
  ASSERT_THAT(a, Eq("100"));
}

TEST(fillRightZero, make1to10) {
  std::string a{"1"};
  fillRightZero(a, 2);
  ASSERT_THAT(a, Eq("10"));
}

TEST(fillRightZero, make0to00) {
  std::string a{"0"};
  fillRightZero(a, 2);
  ASSERT_THAT(a, Eq("00"));
}
// TEST(TestBnum, CheckBelowZeroValuesThrowExceptions)
// {
//   EXPECT_THROW({
//     Coordinates cor = Coordinates(0, 1, 0);
//     cor.getAlt();
//   }, std::invalid_argument);
//   EXPECT_THROW({
//     Coordinates cor = Coordinates(-1.0, 1, 0);
//     cor.getAlt();
//   }, std::invalid_argument);
//   EXPECT_THROW({
//     Coordinates cor = Coordinates(1.0, -11.0, 0);
//     cor.getAlt();
//   }, std::invalid_argument);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
