#include <boost/algorithm/string/join.hpp>

#include "messages/commands/list_command.h"

using boost::algorithm::join;

list_command::list_command(vector<string> channels, string target, string prefix)
	: abstract_message(command, prefix), channels(channels), target(target)
{
}

string list_command::serialize() const
{
    string serialized = abstract_message::serialize() + command;

    serialized += join(channels, ",");

    if (target.size())
        serialized += " " + target;

    return serialized;
}
