#include <string>

#include "messages/motd.h"

using std::string;

abstract_motd::abstract_motd(string prefix, string nick, string message, string command)
	: abstract_message(prefix), nick(nick), message(message), command(command)
{
}

string abstract_motd::serialize() const
{
    return abstract_message::serialize() + command + " " + nick + " " + message;
}

string abstract_motd::get_command() const
{
	return command;
}

motd_start::motd_start(string prefix, string nick, string message)
    : abstract_motd(prefix, nick, message, command)
{
}

motd::motd(string prefix, string nick, string message)
    : abstract_motd(prefix, nick, message, command)
{
}

motd_end::motd_end(string prefix, string nick, string message)
    : abstract_motd(prefix, nick, message, command)
{
}
