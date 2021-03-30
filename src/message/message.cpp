#include "message.h"

Message::Message(std::string message)
{
    extract_prefix(message);
    extract_command(message);
    extract_parameters(message);
}

void Message::extract_prefix(std::string &message)
{
    if (message.at(0) != ':')
        return;

    auto pos = message.find_first_of(' ', 1);
    this->prefix = message.substr(1, pos - 1);

    if (pos == std::string::npos) {
        message = "";
        return;
    }

    message = message.substr(pos + 1);
}

void Message::extract_command(std::string &message)
{
    auto pos = message.find_first_of(' ');
    this->command = message.substr(0, pos);

    if (pos == std::string::npos) {
        message = "";
        return;
    }

    message = message.substr(pos + 1);
}

void Message::extract_parameters(std::string &message)
{
    auto pos = message.find_first_of(" :");

    while (pos != std::string::npos) {
        switch (message.at(pos)) {
            case ' ':
                this->parameters.push_back(message.substr(0, pos));
                message = message.substr(pos + 1);
                break;
            case ':':
                this->parameters.push_back(message.substr(pos + 1));
                return;
        }
        pos = message.find_first_of(" :");
    }

    if (!message.empty())
        this->parameters.push_back(message);
}