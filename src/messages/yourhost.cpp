#include "messages/yourhost.h"

yourhost::yourhost(string prefix, string nickname, string message)
    : abstract_message(prefix), nickname(nickname), message(message)
{
}

string yourhost::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}

string yourhost::get_command() const
{
	return command;
}
