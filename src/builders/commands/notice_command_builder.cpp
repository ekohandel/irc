#include "builders/commands/notice_command_builder.h"
#include "messages/commands/notice_command.h"

unique_ptr<abstract_message> notice_command_builder::build(build_digest digest) const
{
	if (digest.command != notice_command::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + notice_command::command + " message");

	return make_unique<notice_command>(digest.params.at(0), digest.params.at(1), digest.prefix);
}
