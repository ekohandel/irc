#pragma once

#include <boost/asio.hpp>
#include <string>
#include <deque>
#include <iostream>

#include "handlers/abstract_handler.h"
#include "builders/abstract_builder.h"
#include "client/abstract_client.h"
#include "channel.h"

using namespace std;
using boost::asio::io_context;
using boost::asio::ip::tcp;

class client : public abstract_client {
    public:
        client(string host, string service);

        void send_message(shared_ptr<abstract_message> message) override;

        void connect(string nick_name, string password, string real_name);
        void disconnect();
        vector<channel> get_channels();

        ~client();

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
        shared_ptr<abstract_handler> concrete_registration_handler = nullptr;
        shared_ptr<abstract_handler> concrete_list_handler = nullptr;

        void start_runner();
        void do_read();
        void do_write();
};
