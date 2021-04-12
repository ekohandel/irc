#include "messages/welcome.h"

welcome::welcome(string prefix, string nickname, string message)
    : abstract_message(prefix), nickname(nickname), message(message)
{
}

string welcome::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}

string welcome::get_command() const
{
	return command;
}
