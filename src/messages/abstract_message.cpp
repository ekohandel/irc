#include <string>

#include "messages/abstract_message.h"

using std::string;

abstract_message::abstract_message(string command, string prefix)
    : command(command), prefix(prefix)
{
}

string abstract_message::get_command() const
{
    return command;
}

string abstract_message::serialize() const
{
    if (!prefix.empty())
        return string{':'} + prefix + " ";
    return string{};
};
