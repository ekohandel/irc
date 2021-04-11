#include <string>

#include "messages/pass.h"

using std::string;

pass::pass(string prefix, string password)
    : abstract_message(prefix), password(password)
{
}

pass::pass(string password)
    : pass(string{}, password)
{
}

string pass::serialize() const
{
	return abstract_message::serialize() + command + " " + password;
}

string pass::get_command() const
{
	return command;
}
