#include "gtest/gtest.h"
#include "client/client_builder.h"

TEST(ClientTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    auto c = client_builder::build("irc-server", "6667");

    c->connect("homer", "Homer Simpson");

    sleep(10);

    c->disconnect();
}
