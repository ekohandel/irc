#include <string>

#include "messages/user.h"

using std::string;

user::user(string prefix, string username, string realname, unsigned mode)
	: abstract_message(prefix), username(username), realname(realname), mode(mode)
{
}

user::user(string username, string realname, unsigned mode)
	:user(string{}, username, realname, mode)
{
}

string user::serialize() const
{
    string serialized = abstract_message::serialize() + command + " " + username + " " + std::to_string(mode) + " * ";

    if (string::npos != realname.find_first_of(' '))
        serialized += ":";

    return serialized + realname;
}

string user::get_command() const
{
	return command;
}
