#include "message.h"

namespace Message {

    Message::Message(std::string message)
    {
        parse(message);
    }

    void Message::parse(std::string message)
    {
        extract_prefix(message);
        extract_command(message);
        extract_parameters(message);
    }

    std::string Message::serialize() const
    {
        std::string message;
        if (!prefix.empty()) {
            message.append(":");
            message.append(prefix);
            message.append(" ");
        }

        message.append(command);

        for (auto parameter: parameters)
        {
            message.append(" ");
            if (std::string::npos != parameter.find(" "))
                message.append(":");
            message.append(parameter);
        }

        return message;
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

    pass::pass()
    {
        command = "PASS";
        parameters.push_back("password");
    }

    nick::nick(std::string name)
    {
        command = "NICK";
        parameters.push_back(name);
    }

    user::user(string user_name, string real_name)
    {
        command = "USER";
        parameters.push_back(user_name);
        parameters.push_back("*");
        parameters.push_back("*");
        parameters.push_back(real_name);
    }

    pong::pong(string server)
    {
        command = "PONG";
        parameters.push_back(server);
    }
}