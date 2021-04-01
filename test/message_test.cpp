#include "gtest/gtest.h"
#include "message.h"

class MessageTest: public Message::Message, public ::testing::Test
{
};

TEST_F(MessageTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    parse("USER");

    EXPECT_EQ(prefix, "");
    EXPECT_EQ(command, "USER");
    EXPECT_EQ(parameters, (std::vector<std::string>{}));
}

TEST_F(MessageTest, ShouldParsePrefixWhenGivenMessageWithoutCommandAndParamters)
{
    parse(":WiZ!jto@tolsun.oulu.fi");

    EXPECT_EQ(prefix, "WiZ!jto@tolsun.oulu.fi");
    EXPECT_EQ(command, "");
    EXPECT_EQ(parameters, (std::vector<std::string>{}));
}

TEST_F(MessageTest, ShouldParsePrefixAndCommandWhenGivenMessageWithoutParameters)
{
    parse(":WiZ!jto@tolsun.oulu.fi USER");

    EXPECT_EQ(prefix, "WiZ!jto@tolsun.oulu.fi");
    EXPECT_EQ(command, "USER");
    EXPECT_EQ(parameters, (std::vector<std::string>{}));
}

TEST_F(MessageTest, ShouldParseCommandAndParametersWhenGivenMessageWithoutPrefix)
{
    parse("USER guest 0 * :Ronnie Reagan");

    EXPECT_EQ(prefix, "");
    EXPECT_EQ(command, "USER");
    EXPECT_EQ(parameters, (std::vector<std::string>{"guest", "0", "*", "Ronnie Reagan"}));
}

TEST_F(MessageTest, ShouldParsePrefixCommandAndParametersWhenGivenMessage)
{
    parse(":WiZ!jto@tolsun.oulu.fi NICK Kilroy");

    EXPECT_EQ(prefix, "WiZ!jto@tolsun.oulu.fi");
    EXPECT_EQ(command, "NICK");
    EXPECT_EQ(parameters, (std::vector<std::string>{"Kilroy"}));
}

TEST_F(MessageTest, ShouldSerializeNickMessage)
{
    command = "NICK";
    parameters.push_back("homer");

    EXPECT_EQ(serialize(), "NICK homer");
}

TEST_F(MessageTest, ShouldSerializeUserMessage)
{
    command = "USER";
    parameters.push_back("homer");
    parameters.push_back("*");
    parameters.push_back("*");
    parameters.push_back("Homer Simpson");

    EXPECT_EQ(serialize(), "USER homer * * :Homer Simpson");
}
