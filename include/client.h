#pragma once

#include <boost/asio.hpp>
#include <string>
#include <deque>

#include "message.h"

using std::deque;
using std::string;
using std::unique_ptr;
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

        void start_runner();
        void send_message(Message::Message message);
        void do_write();
        void do_read();

    public:
        Client(string host, string service);
        ~Client();
        void connect_as(string user_name, string real_name);
        void disconnect();
};
