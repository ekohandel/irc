#include <boost/asio.hpp>

#include "client.h"

Client::Client(std::string host, std::string service)
    : host(host), service(service)
{
}

void Client::Connect()
{
    boost::asio::ip::tcp::resolver resolver(io_context);

    auto endpoints = resolver.resolve(host, service);
    socket = std::make_unique<boost::asio::ip::tcp::socket>(io_context);

    boost::asio::connect(*socket, endpoints);

    //HACK: to test that we can actually send something
    std::array<char, 11> buffer {"NICK abe\r\n"};
    boost::system::error_code error;
    socket->write_some(boost::asio::buffer(buffer), error);
}
