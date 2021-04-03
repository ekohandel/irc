#include "gtest/gtest.h"
#include "client.h"

TEST(ClientTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    Client client("irc-server", "6667");

    client.connect_as("homer", "Homer Simpson");

    sleep(10);

    client.disconnect();
}
