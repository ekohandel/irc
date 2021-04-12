#pragma once

#include <boost/asio.hpp>
#include <string>
#include <deque>
#include <iostream>

#include "messages/abstract_builder.h"
#include "handlers/abstract_handler.h"
#include "messages/pass.h"
#include "messages/nick.h"
#include "messages/user.h"

using std::deque;
using std::string;
using std::unique_ptr;
using boost::asio::io_context;
using boost::asio::ip::tcp;
using std::thread;

class client
{
    public:
        client(string host, string service);
        ~client();
        shared_ptr<abstract_handler> add_handler(shared_ptr<abstract_handler> delegate);
        shared_ptr<abstract_builder> add_builder(shared_ptr<abstract_builder> delegate);
        void connect(string nick_name, string password, string real_name);
        void disconnect();
        vector<string> get_channels();

    private:
        io_context executer;
        unique_ptr<thread> runner;
        unique_ptr<tcp::socket> socket;
        string host;
        string service;
        string nick_name;
        string real_name;
        deque<string> write_messages;
        boost::asio::streambuf read_buffer;
        const char *message_delimiter = "\r\n";
        shared_ptr<abstract_builder> message_builder = nullptr;
        shared_ptr<abstract_handler> message_handler = nullptr;
        shared_ptr<abstract_handler> registration_handler_ = nullptr;
        shared_ptr<abstract_handler> list_handler_ = nullptr;

        void start_runner();
        void do_read();
        void do_write();
        void send_message(shared_ptr<abstract_message> message);
};
