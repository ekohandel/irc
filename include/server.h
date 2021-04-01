#pragma once

#include <string>

class Server {
    private:
        std::string name;
    
    public:
        const unsigned maximum_name_length = 63;

        Server(std::string name);
};