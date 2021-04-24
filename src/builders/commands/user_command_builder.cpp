#include "builders/commands/user_command_builder.h"
#include "messages/commands/user_command.h"

unique_ptr<abstract_message> user_command_builder::build(build_digest digest) const
{
	if (digest.command != user_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 4)
		throw std::invalid_argument(string{"Malformed "} + user_command::command + " message");

	return make_unique<user_command>(digest.params.at(0), digest.params.at(3), 0, digest.prefix);
}
