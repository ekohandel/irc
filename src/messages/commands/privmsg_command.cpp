#include "messages/commands/privmsg_command.h"

privmsg_command::privmsg_command(string target, string text, string prefix)
    : abstract_message(command, prefix), target(target), text(text)
{
}

string privmsg_command::serialize() const
{
	string serialized = abstract_message::serialize() + command;

    serialized += " " + target + " ";
    if (string::npos != text.find_first_of(' '))
        serialized += ":";
    serialized += text;

	return serialized;
}
