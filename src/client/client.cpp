#include <boost/asio.hpp>
#include <string>
#include <iostream>
#include <string_view>

#include "client.h"
#include "message.h"

using std::make_unique;

const char *message_delimiter = "\r\n";

Client::Client(string host, string service)
    : host(host), service(service)
{
}

Client::~Client()
{
    if (runner)
        runner->join();
}

void Client::connect_as(string user_name, string real_name)
{
    user_name = user_name;
    real_name = real_name;

    tcp::resolver resolver(executer);

    auto endpoints = resolver.resolve(host, service);
    socket = make_unique<tcp::socket>(executer);

    boost::asio::async_connect(*socket, endpoints,
        [this, user_name, real_name](boost::system::error_code ec, tcp::endpoint)
        {
            if (ec)
                socket->close();
            else {
                do_read();
                send_message(Message::pass{});
                send_message(Message::nick{user_name});
                send_message(Message::user{user_name, real_name});
            }
        }
    );

    start_runner();
}

void Client::disconnect()
{
    executer.stop();
    socket->close();
}

void Client::do_read()
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

                Message::Message message(string{text.begin(), text.end() - strlen(message_delimiter)});
                std::cout << message.serialize() << std::endl;

                do_read();

                // HACK: just respond to ping for now
                // need to restructure messages and allow for defining
                // handlers for message types
                if (message.command == "PING")
                    send_message(Message::pong{message.parameters[0]});
            }
        });
}

void Client::do_write()
{
    string message = write_messages.front();

    std::cout << "Sending: " << message << std::endl;

    boost::asio::async_write(*socket,
        boost::asio::buffer(message, message.length()),
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

void Client::send_message(Message::Message message)
{
    auto text = message.serialize().append(message_delimiter);
    auto initiate_write = write_messages.empty();
    write_messages.push_back(text);
    if (initiate_write)
        do_write();
}

void Client::start_runner()
{
    runner = std::make_unique<std::thread>([this]() { executer.run(); });
}