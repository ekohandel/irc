#include "messages/replies/created_reply.h"

created_reply::created_reply(string nickname, string message, string prefix)
    : abstract_message(command, prefix), nickname(nickname), message(message)
{
}

string created_reply::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}
