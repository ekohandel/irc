#include "builders/commands/privmsg_command_builder.h"
#include "messages/commands/privmsg_command.h"

unique_ptr<abstract_message> privmsg_command_builder::build(build_digest digest) const
{
	if (digest.command != privmsg_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + privmsg_command::command + " message");

	return make_unique<privmsg_command>(digest.params.at(0), digest.params.at(1), digest.prefix);
}
