#include <boost/algorithm/string/join.hpp>

#include "messages/commands/join_command.h"

using namespace std;
using boost::algorithm::join;

join_command::join_command(vector<string> channels, vector<string> keys, string prefix)
	: abstract_message(command, prefix), channels(channels), keys(keys)
{
}

string join_command::serialize() const
{
	string serialized = abstract_message::serialize() + command;

	serialized += " " + join(channels, ",");

	if (keys.size())
		serialized += " " + join(keys, ",");

	return serialized;
}
