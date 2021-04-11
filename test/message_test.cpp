#include "gtest/gtest.h"

#include "messages/nick_builder.h"
#include "messages/pass_builder.h"
#include "messages/ping_builder.h"
#include "messages/pong_builder.h"
#include "messages/user_builder.h"

using std::unique_ptr;
using std::make_unique;
using std::make_shared;

class MessageTest: public ::testing::Test
{
    public:
        shared_ptr<abstract_builder> handler;

        void SetUp() override {
            (handler = make_shared<pass_builder>())
                ->add_builder(make_shared<nick_builder>())
                ->add_builder(make_shared<user_builder>())
                ->add_builder(make_shared<ping_builder>())
                ->add_builder(make_shared<pong_builder>())
            ;
        }
};

TEST_F(MessageTest, UnsupportedMessageFails)
{
    const string text = "FOO foo";
    auto thrown = false;

    try {
        handler->build(text);
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), string{"Unsupported message type: FOO"});
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, MalformedEmptyMessageFails)
{
    const string text = "";
    auto thrown = false;

    try {
        handler->build(text);
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), "Malformed message: " + text);
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, MalformedPrefixOnlyMessageFails)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi";
    auto thrown = false;

    try {
        handler->build(text);
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), "Malformed message: " + text);
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, PassMessageWithoutPrefix)
{
    const string text = "PASS password";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, PassMessageExplicit)
{
    auto msg = make_unique<pass>("password");
    const string text = "PASS password";
    EXPECT_EQ(msg->serialize(), text);
}

TEST_F(MessageTest, PassMessageWithPrefix)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi PASS password";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, PassMessageWithTooManyParams)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi PASS password1 password2";
    auto thrown = false;

    try {
        handler->build(text)->serialize();
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), string{"Malformed PASS message"});
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, NickMessageWithoutPrefix)
{
    const string text = "NICK nickname";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, NickMessageWithPrefix)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi NICK nickname";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, NickMessageWithTooManyParams)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi NICK nickname1 nickname2";
    auto thrown = false;

    try {
        handler->build(text)->serialize();
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), string{"Malformed NICK message"});
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, UserMessageWithoutPrefix)
{
    const string text = "USER homer 0 * :Homer Simpson";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, UserMessageWithPrefix)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi USER homer 0 * :Homer Simpson";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, UserMessageWithTooManyParams)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi USER homer 0 simpson * :Homer Simpson";
    auto thrown = false;

    try {
        handler->build(text)->serialize();
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), string{"Malformed USER message"});
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, PingMessageWithoutPrefix)
{
    const string text = "PING server1 server2";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, PingMessageWithPrefix)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi PING server1 server2";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, PingMessageWithTooManyParams)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi PING";
    auto thrown = false;

    try {
        handler->build(text)->serialize();
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), string{"Malformed PING message"});
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}

TEST_F(MessageTest, PongMessageWithoutPrefix)
{
    const string text = "PONG server1 server2";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, PongMessageWithPrefix)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi PONG server1 server2";
    EXPECT_EQ(handler->build(text)->serialize(), text);
}

TEST_F(MessageTest, PongMessageWithTooManyParams)
{
    const string text = ":WiZ!jto@tolsun.oulu.fi PONG";
    auto thrown = false;

    try {
        handler->build(text)->serialize();
    } catch (std::invalid_argument e) {
        EXPECT_EQ(e.what(), string{"Malformed PONG message"});
        thrown = true;
    }
    EXPECT_TRUE(thrown);
}
