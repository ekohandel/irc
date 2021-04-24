#include "messages/commands/pass_command.h"

pass_command::pass_command(string password, string prefix)
    : abstract_message(command, prefix), password(password)
{
}

string pass_command::serialize() const
{
	return abstract_message::serialize() + command + " " + password;
}
