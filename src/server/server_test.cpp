#include <stdexcept>

#include "gtest/gtest.h"
#include "server.h"

TEST(ServerTest, ShouldConstructServerWithValidName)
{
    Server server("Hello");
    EXPECT_FALSE(0);
}

TEST(ServerTest, ShouldThrowInvalidArgumentExceptionForTooLongServerName)
{
    EXPECT_THROW(
        Server server("OneTwoThreeFourFiveSixSevenEightNineTenElevenTwelveThirteenFourteenFifteen"),
        std::invalid_argument
    );
}
