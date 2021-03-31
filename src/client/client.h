#pragma once

#include <boost/asio.hpp>
#include <string>

class Client
{
    private:
        boost::asio::io_context io_context;
        std::unique_ptr<boost::asio::ip::tcp::socket> socket;
        std::string host;
        std::string service;

    public:
        Client(std::string host, std::string service);
        void Connect();
};
