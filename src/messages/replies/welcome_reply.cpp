#include "messages/replies/welcome_reply.h"

welcome_reply::welcome_reply(string nickname, string message, string prefix)
    : abstract_message(command, prefix), nickname(nickname), message(message)
{
}

string welcome_reply::serialize() const
{
	return abstract_message::serialize() + command + " " + message;
}
