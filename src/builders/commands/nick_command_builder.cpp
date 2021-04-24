#include "builders/commands/nick_command_builder.h"
#include "messages/commands/nick_command.h"

unique_ptr<abstract_message> nick_command_builder::build(build_digest digest) const
{
	if (digest.command != nick_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 1)
		throw std::invalid_argument(string{"Malformed "} + nick_command::command + " message");

	return make_unique<nick_command>(digest.params.at(0), digest.prefix);
}
