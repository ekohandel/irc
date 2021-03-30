#include <stdexcept>

#include "server.h"

Server::Server(std::string name) {
    if (name.length() > Server::maximum_name_length)
        throw std::invalid_argument("name");

    this->name = name;
}