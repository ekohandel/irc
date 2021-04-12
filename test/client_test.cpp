#include "gtest/gtest.h"
#include "client/client.h"

TEST(ClientTest, ShouldParseCommandWhenGivenMessageWithoutPrefixAndParameters)
{
    auto c = client("irc-server", "6667");

    c.connect("homer", "password", "Homer Simpson");

    auto chans = c.get_channels();
    std::cout << "Channels: " << std::endl;
    for (auto chan : chans)
        std::cout << chan << std::endl;

    c.disconnect();
}
