#include "builders/replies/welcome_reply_builder.h"
#include "messages/replies/welcome_reply.h"

unique_ptr<abstract_message> welcome_reply_builder::build(build_digest digest) const
{
	if (digest.command != welcome_reply::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + welcome_reply::command + " message");

	return make_unique<welcome_reply>(digest.params.at(0), digest.params.at(1), digest.prefix);
}
