#pragma once

#include <boost/asio.hpp>
#include <string>
#include <deque>
#include <iostream>

#include "message.h"
#include "messages.h"
#include "handler.h"

using std::deque;
using std::string;
using std::unique_ptr;
using std::make_unique;
using boost::asio::io_context;
using boost::asio::ip::tcp;
using std::thread;

class Client
{
    private:
        io_context executer;
        unique_ptr<thread> runner;
        unique_ptr<tcp::socket> socket;
        string host;
        string service;
        string user_name;
        string real_name;
        deque<string> write_messages;
        boost::asio::streambuf read_buffer;
        const char *message_delimiter = "\r\n";
        builder *message_builder = nullptr;
        handler *message_handler = nullptr;

        void start_runner() {
            runner = std::make_unique<std::thread>(
                [this]() {
                    executer.run();
                }
            );
        }

        void do_read() {
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
                            unique_ptr<message> msg = message_builder->build(string{text.begin(), text.end() - strlen(message_delimiter)});
                            message_handler->handle(msg.get(), *this);
                        } catch (std::invalid_argument e) {
                            std::cerr << e.what() << std::endl;
                        }
                    }
                });
        }
        void do_write() {
            string msg = write_messages.front();

            std::cout << "Sending: " << msg << std::endl;

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

    public:
        Client(string host, string service) : host(host), service(service) {}

        ~Client() {
            delete message_builder;
            delete message_handler;
            if (runner)
                runner->join();
        }

        handler *add_handler(handler *delegate) {
            if (message_handler)
                return message_handler->add_handler(delegate);
            message_handler = delegate;
            return message_handler;
        }

        builder *add_builder(builder *delegate) {
            if (message_builder)
                return message_builder->add_builder(delegate);
            message_builder = delegate;
            return message_builder;
        }

        void send_message(unique_ptr<message> &msg) {
            auto text = msg->serialize().append(message_delimiter);
            auto initiate_write = write_messages.empty();
            write_messages.push_back(text);
            if (initiate_write)
                do_write();
        }

        void connect(string user_name, string real_name) {
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
                        unique_ptr<message> msg = make_unique<pass>("password");
                        send_message(msg);
                        msg = make_unique<nick>(user_name);
                        send_message(msg);
                        msg = make_unique<user>(user_name, real_name);
                        send_message(msg);
                    }
                }
            );

            start_runner();
        }

        void disconnect() {
            executer.stop();
            socket->close();
        }
};
