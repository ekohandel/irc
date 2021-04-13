#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>

#include "messages/motd_builder.h"
#include "messages/nick_builder.h"
#include "messages/pass_builder.h"
#include "messages/ping_builder.h"
#include "messages/pong_builder.h"
#include "messages/user_builder.h"
#include "messages/notice_builder.h"
#include "messages/welcome_builder.h"
#include "messages/created_builder.h"
#include "messages/myinfo_builder.h"
#include "messages/yourhost_builder.h"

#include "handlers/ping_handler.h"
#include "handlers/motd_handler.h"
#include "handlers/notice_handler.h"
#include "handlers/registration_handler.h"
#include "handlers/list_handler.h"

#include "client/client.h"
#include "messages/list.h"

using std::make_unique;
using std::make_shared;

client::client(string host, string service)
    : host(host), service(service)
{
    boost::log::core::get()->set_filter
    (
        boost::log::trivial::severity >= boost::log::trivial::trace
    );

    add_builder(make_shared<pass_builder>())
        ->add_builder(make_shared<nick_builder>())
        ->add_builder(make_shared<user_builder>())
        ->add_builder(make_shared<ping_builder>())
        ->add_builder(make_shared<pong_builder>())
        ->add_builder(make_shared<notice_builder>())
        ->add_builder(make_shared<motd_start_builder>())
        ->add_builder(make_shared<motd_builder>())
        ->add_builder(make_shared<motd_end_builder>())
        ->add_builder(make_shared<welcome_builder>())
        ->add_builder(make_shared<created_builder>())
        ->add_builder(make_shared<yourhost_builder>())
        ->add_builder(make_shared<myinfo_builder>())
        ->add_builder(make_shared<list_channel_builder>())
        ->add_builder(make_shared<list_channel_end_builder>())
    ;

    concrete_registration_handler = make_shared<registration_handler>();
    concrete_list_handler = make_shared<list_handler>();

    add_handler(make_shared<ping_handler>())
        ->add_handler(make_shared<motd_handler>())
        ->add_handler(make_shared<notice_handler>())
        ->add_handler(concrete_registration_handler)
        ->add_handler(concrete_list_handler)
    ;
}

client::~client()
{
    if (runner)
        runner->join();
}

shared_ptr<abstract_handler> client::add_handler(shared_ptr<abstract_handler> delegate)
{
    if (root_message_handler)
        return root_message_handler->add_handler(delegate);
    root_message_handler = delegate;
    return root_message_handler;
}

shared_ptr<abstract_builder> client::add_builder(shared_ptr<abstract_builder> delegate)
{
    if (root_message_builder)
        return root_message_builder->add_builder(delegate);
    root_message_builder = delegate;
    return root_message_builder;
}

void client::connect(string nick_name, string password, string real_name)
{
    nick_name = nick_name;
    real_name = real_name;

    tcp::resolver resolver(executer);

    auto endpoints = resolver.resolve(host, service);
    socket = make_unique<tcp::socket>(executer);

    boost::asio::connect(*socket, endpoints);

    do_read();
    start_runner();

    if (!password.empty())
        send_message(make_shared<pass>(password));
    send_message(make_shared<nick>(nick_name));
    send_message(make_shared<user>(nick_name, real_name));

    concrete_registration_handler->wait();
}

void client::disconnect()
{
    executer.stop();
    socket->close();
}

vector<string> client::get_channels()
{
    auto handler = static_pointer_cast<list_handler>(concrete_list_handler);

    handler->channels = {};

    send_message(make_shared<list>());

    handler->wait();

    return handler->channels;
}

void client::start_runner()
{
    runner = std::make_unique<std::thread>(
        [this]() {
            executer.run();
        }
    );
}

void client::do_read()
{
    boost::asio::async_read_until(*socket,
        read_buffer, message_delimiter,
        [this](boost::system::error_code ec, std::size_t size) {
            if (ec)
                socket->close();
            else {
                std::istream reader(&read_buffer);
                std::vector<char> text(size);
                reader.read(text.data(), size);

                do_read();

                try {
                    string s = string{text.begin(), text.end() - strlen(message_delimiter)};

                    BOOST_LOG_TRIVIAL(trace) << string{"Received: "} + s;

                    shared_ptr<abstract_message> message = root_message_builder->build(s);
                    auto reply = root_message_handler->handle(message);
                    if (reply)
                        send_message(reply);
                } catch (std::invalid_argument e) {
                    BOOST_LOG_TRIVIAL(warning) << e.what();
                }
            }
        });
}

void client::do_write()
{
    string msg = write_messages.front();

    boost::asio::async_write(*socket,
        boost::asio::buffer(msg, msg.length()),
        [this](boost::system::error_code ec, std::size_t)
        {
            if (ec)
                socket->close();
            else {
                write_messages.pop_front();
                if (!write_messages.empty())
                    do_write();
            }
        }
    );
}

void client::send_message(shared_ptr<abstract_message> message)
{
    auto text = message->serialize();

    BOOST_LOG_TRIVIAL(trace) << string{"Sending: "} + text;

    text = text.append(message_delimiter);
    auto initiate_write = write_messages.empty();
    write_messages.push_back(text);
    if (initiate_write)
        do_write();
}
