#include "gtest/gtest.h"
#include "client.h"

TEST(ClientTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    Client client("irc-server", "6667");

    client.Connect();
}
