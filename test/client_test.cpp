#include "gtest/gtest.h"
#include "client_builder.h"

TEST(ClientTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    Client *client = client_builder::build("irc-server", "6667");

    client->connect("homer", "Homer Simpson");

    sleep(10);

    client->disconnect();

    delete client;
}
