#include <string>

#include "messages/notice.h"

using std::string;

notice::notice(string prefix, string target, string text)
	: abstract_message(prefix), target(target), text(text)
{
}

string notice::serialize() const
{
    return abstract_message::serialize() + command + " " + target + " " + text;
}

string notice::get_command() const
{
	return command;
}
