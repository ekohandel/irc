#include "gtest/gtest.h"
#include "client.h"

TEST(ClientTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    Client client("localhost", "6667");

    client.Connect();
}
