#include "builders/commands/ping_command_builder.h"
#include "messages/commands/ping_command.h"

unique_ptr<abstract_message> ping_command_builder::build(build_digest digest) const
{
	if (digest.command != ping_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() == 0)
		throw std::invalid_argument(string{"Malformed "} + ping_command::command + " message");

	return make_unique<ping_command>(digest.params, digest.prefix);
}
