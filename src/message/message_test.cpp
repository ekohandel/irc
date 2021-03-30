#include "gtest/gtest.h"
#include "message.h"

TEST(MessageTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    Message message("USER");

    EXPECT_EQ(message.prefix, "");
    EXPECT_EQ(message.command, "USER");
    EXPECT_EQ(message.parameters, (std::vector<std::string>{}));
}

TEST(MessageTest, ShouldParsePrefixWhenGivenMessageWithoutCommandAndParamters)
{
    Message message(":WiZ!jto@tolsun.oulu.fi");

    EXPECT_EQ(message.prefix, "WiZ!jto@tolsun.oulu.fi");
    EXPECT_EQ(message.command, "");
    EXPECT_EQ(message.parameters, (std::vector<std::string>{}));
}

TEST(MessageTest, ShouldParsePrefixAndCommandWhenGivenMessageWithoutParameters)
{
    Message message(":WiZ!jto@tolsun.oulu.fi USER");

    EXPECT_EQ(message.prefix, "WiZ!jto@tolsun.oulu.fi");
    EXPECT_EQ(message.command, "USER");
    EXPECT_EQ(message.parameters, (std::vector<std::string>{}));
}

TEST(MessageTest, ShouldParseCommandAndParametersWhenGivenMessageWithoutPrefix)
{
    Message message("USER guest 0 * :Ronnie Reagan");

    EXPECT_EQ(message.prefix, "");
    EXPECT_EQ(message.command, "USER");
    EXPECT_EQ(message.parameters, (std::vector<std::string>{"guest", "0", "*", "Ronnie Reagan"}));
}

TEST(MessageTest, ShouldParsePrefixCommandAndParametersWhenGivenMessage)
{
    Message message(":WiZ!jto@tolsun.oulu.fi NICK Kilroy");

    EXPECT_EQ(message.prefix, "WiZ!jto@tolsun.oulu.fi");
    EXPECT_EQ(message.command, "NICK");
    EXPECT_EQ(message.parameters, (std::vector<std::string>{"Kilroy"}));
}
