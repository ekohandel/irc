#include <stdexcept>

#include "messages/commands/ping_command.h"

ping_command::ping_command(vector<string> servers, string prefix)
    : abstract_message(command, prefix), servers(servers)
{
    if (servers.empty())
        throw std::invalid_argument(string{"Malformed "} + command + " message");
}

string ping_command::serialize() const
{
	string serialized = abstract_message::serialize() + command;

	for (auto server: servers)
		serialized += " " + server;

	return serialized;
}
