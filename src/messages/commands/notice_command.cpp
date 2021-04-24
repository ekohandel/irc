#include "messages/commands/notice_command.h"

notice_command::notice_command(string target, string text, string prefix)
	: abstract_message(command, prefix), target(target), text(text)
{
}

string notice_command::serialize() const
{
    return abstract_message::serialize() + command + " " + target + " " + text;
}
