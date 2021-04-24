#include "builders/replies/yourhost_reply_builder.h"
#include "messages/replies/yourhost_reply.h"

unique_ptr<abstract_message> yourhost_reply_builder::build(build_digest digest) const
{
	if (digest.command != yourhost_reply::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + yourhost_reply::command + " message");

	return make_unique<yourhost_reply>(digest.params.at(0), digest.params.at(1), digest.prefix);
}
