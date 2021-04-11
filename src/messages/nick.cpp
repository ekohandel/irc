#include <string>

#include "messages/nick.h"

nick::nick(string prefix, string nickname)
	: abstract_message(prefix), nickname(nickname)
{
}

nick::nick(string nickname)
	: nick(string{}, nickname)
{
}

string nick::serialize() const
{
	return abstract_message::serialize() + command + " " + nickname;
}

string nick::get_command() const
{
	return command;
}
