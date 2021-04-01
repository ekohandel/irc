#pragma once

#include <string>
#include <vector>

using std::vector;
using std::string;

namespace Message {
    class Message {
        private:
            void extract_prefix(string &messsage);
            void extract_command(string &messsage);
            void extract_parameters(string &message);

        public:
            // HACK: need to remove these and restructure
            // messages
            string command;
            string prefix;
            vector<string> parameters;

            Message() = default;
            Message(string message);
            void parse(string message);
            string serialize() const;
    };

    class pass: public Message
    {
        public:
            pass();
    };

    class nick: public Message
    {
        public:
            nick(string name);
    };

    class user: public Message
    {
        public:
            user(string user_name, string real_name);
    };

    class pong: public Message
    {
        public:
            pong(string server);
    };
}