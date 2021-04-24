#include "builders/commands/pass_command_builder.h"
#include "messages/commands/pass_command.h"

unique_ptr<abstract_message> pass_command_builder::build(build_digest digest) const
{
	if (digest.command != pass_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 1)
		throw std::invalid_argument(string{"Malformed "} + pass_command::command + " message");

	return make_unique<pass_command>(digest.params.at(0), digest.prefix);
}
