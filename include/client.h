#pragma once

#include <boost/asio.hpp>
#include <string>
#include <deque>

#include "message.h"

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
        builder *handler;

        void start_runner() {
            runner = std::make_unique<std::thread>(
                [this]() {
                    executer.run();
                }
            );
        }

        void send_message(unique_ptr<message> &msg) {
            auto text = msg->serialize().append(message_delimiter);
            auto initiate_write = write_messages.empty();
            write_messages.push_back(text);
            if (initiate_write)
                do_write();
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
                            unique_ptr<message> msg = handler->build(string{text.begin(), text.end() - strlen(message_delimiter)});

                            // HACK: just respond to ping for now
                            // need to restructure messages and allow for defining
                            // handlers for message types
                            ping *ping_msg = dynamic_cast<ping*>(msg.get());
                            if (ping_msg) {
                                unique_ptr<message> pong_msg = make_unique<pong>(ping_msg->servers);
                                send_message(pong_msg);
                            }
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
        Client(string host, string service) : host(host), service(service) {
            (handler = new template_builder<pass>())
                ->set_next(new template_builder<nick>())
                ->set_next(new template_builder<user>())
                ->set_next(new template_builder<ping>())
                ->set_next(new template_builder<pong>())
                ->set_next(new template_builder<notice>())
            ;
        }

        ~Client() {
            delete handler;
            if (runner)
                runner->join();
        }

        void connect_as(string user_name, string real_name) {
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
                        msg = make_unique<nick>(real_name);
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
