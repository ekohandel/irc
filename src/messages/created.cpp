#include "messages/created.h"

created::created(string prefix, string nickname, string message)
    : abstract_message(prefix), nickname(nickname), message(message)
{
}

string created::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}

string created::get_command() const
{
	return command;
}
