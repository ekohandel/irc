#include "messages/myinfo.h"

myinfo::myinfo(string prefix, string nickname, string message)
    : abstract_message(prefix), nickname(nickname), message(message)
{
}

string myinfo::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}

string myinfo::get_command() const
{
	return command;
}
