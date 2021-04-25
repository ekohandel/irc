#include "builders/commands/join_command_builder.h"
#include "messages/commands/join_command.h"

unique_ptr<abstract_message> join_command_builder::build(build_digest digest) const
{
	if (digest.command != join_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 1)
		throw std::invalid_argument(string{"Malformed "} + join_command::command + " message");

	return make_unique<join_command>(vector<string>{digest.params.at(0)}, vector<string>{}, digest.prefix);
}
