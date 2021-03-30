#pragma once

#include <string>
#include <vector>

class Message {
    private:
        void extract_prefix(std::string &messsage);
        void extract_command(std::string &messsage);
        void extract_parameters(std::string &message);

    public:
        std::string prefix;
        std::string command;
        std::vector<std::string> parameters;

        Message(std::string message);
};