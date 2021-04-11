#include <stdexcept>

#include "messages/pong.h"

pong::pong(string prefix, vector<string> servers)
    : abstract_message(prefix), servers(servers)
{
	if (servers.empty())
		throw std::invalid_argument(string{"Malformed "} + command + " message");
}

pong::pong(vector<string> servers)
	: pong("", servers)
{
}

string pong::serialize() const
{
	string serialized = abstract_message::serialize() + command;

	for (auto server: servers)
		serialized += " " + server;
	return serialized;
}

string pong::get_command() const
{
	return command;
}
