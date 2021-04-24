#include "messages/replies/yourhost_reply.h"

yourhost_reply::yourhost_reply(string nickname, string message, string prefix)
    : abstract_message(command, prefix), nickname(nickname), message(message)
{
}

string yourhost_reply::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}
