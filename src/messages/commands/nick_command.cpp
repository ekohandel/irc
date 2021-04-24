#include "messages/commands/nick_command.h"

nick_command::nick_command(string nickname, string prefix)
	: abstract_message(command, prefix), nickname(nickname)
{
}

string nick_command::serialize() const
{
	return abstract_message::serialize() + command + " " + nickname;
}
