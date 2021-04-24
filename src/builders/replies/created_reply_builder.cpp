#include "builders/replies/created_reply_builder.h"
#include "messages/replies/created_reply.h"

unique_ptr<abstract_message> created_reply_builder::build(build_digest digest) const
{
	if (digest.command != created_reply::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + created_reply::command + " message");

	return make_unique<created_reply>(digest.params.at(0), digest.params.at(1), digest.prefix);
}
