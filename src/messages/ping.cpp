#include "messages/ping.h"

ping::ping(string prefix, vector<string> servers)
    : abstract_message(prefix), servers(servers)
{
    if (servers.empty())
        throw std::invalid_argument(string{"Malformed "} + command + " message");
}

ping::ping(vector<string> servers)
    : ping("", servers)
{
}

string ping::serialize() const
{
	string serialized = abstract_message::serialize() + command;

	for (auto server: servers)
		serialized += " " + server;

	return serialized;
}

string ping::get_command() const
{
	return command;
}
