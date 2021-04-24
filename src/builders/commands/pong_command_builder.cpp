#include "builders/commands/pong_command_builder.h"
#include "messages/commands/pong_command.h"

unique_ptr<abstract_message> pong_command_builder::build(build_digest digest) const
{
	if (digest.command != pong_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() == 0)
		throw std::invalid_argument(string{"Malformed "} + pong_command::command + " message");

	return make_unique<pong_command>(digest.params, digest.prefix);
}
