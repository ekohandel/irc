#include "messages/replies/myinfo_reply.h"

myinfo_reply::myinfo_reply(string nickname, string message, string prefix)
    : abstract_message(command, prefix), nickname(nickname), message(message)
{
}

string myinfo_reply::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}
