#include "messages/commands/user_command.h"

user_command::user_command(string username, string realname, unsigned mode, string prefix)
	: abstract_message(command, prefix), username(username), realname(realname), mode(mode)
{
}

string user_command::serialize() const
{
    string serialized = abstract_message::serialize() + command + " " + username + " " + std::to_string(mode) + " * ";

    if (string::npos != realname.find_first_of(' '))
        serialized += ":";

    return serialized + realname;
}
