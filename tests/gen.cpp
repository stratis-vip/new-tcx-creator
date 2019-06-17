#include "gmock/gmock.h"
#include "route.hpp"

using namespace testing;

class TestCoordinates : public Test
{
public:
  Coordinates cor{2, 1, 3};
};

TEST_F(TestCoordinates, CheckInitValues)
{
  ASSERT_THAT(cor.getLat(), Eq(1.0));
  ASSERT_THAT(cor.getLon(), Eq(2.0));
  ASSERT_THAT(cor.getAlt(), Eq(3.0));
}

TEST(TestInvalidCoordinates, CheckBelowZeroValuesThrowExceptions)
{
  EXPECT_THROW({
    Coordinates cor = Coordinates(0, 1, 0);
    cor.getAlt();
  }, std::invalid_argument);
  EXPECT_THROW({
    Coordinates cor = Coordinates(-1.0, 1, 0);
    cor.getAlt();
  }, std::invalid_argument);
  EXPECT_THROW({
    Coordinates cor = Coordinates(1.0, -11.0, 0);
    cor.getAlt();
  }, std::invalid_argument);
}

/*---------Route Tests ------------*/

class TestRoute : public Test
{
public:
  Route route = Route();
  TestRoute()
  {
    route.add(aCord);
  }
private:
  Coordinates aCord{3, 2, 4};
};

TEST_F(TestRoute, CheckInitValues)
{
  ASSERT_THAT(route.size(), Eq(1));
}

TEST_F(TestRoute, CheckQuoteOperator)
{
  ASSERT_THAT(route[0].getAlt(), Eq(4.0));
  ASSERT_THAT(route[0].getLat(), Eq(2.0));
  ASSERT_THAT(route[0].getLon(), Eq(3.0));
}

TEST_F(TestRoute, CheckRangeOperators)
{
  for (auto i = route.begin(); i != route.begin() + 1; i++)
  {
    Coordinates aC = *i;
    ASSERT_THAT(aC.getAlt(), Eq(4.0));
    ASSERT_THAT(aC.getLat(), Eq(2.0));
    ASSERT_THAT(aC.getLon(), Eq(3.0));
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
