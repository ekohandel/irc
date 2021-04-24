#include "builders/replies/myinfo_reply_builder.h"
#include "messages/replies/myinfo_reply.h"

unique_ptr<abstract_message> myinfo_reply_builder::build(build_digest digest) const
{
	if (digest.command != myinfo_reply::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 6)
		throw std::invalid_argument(string{"Malformed "} + myinfo_reply::command + " message");

	return make_unique<myinfo_reply>(digest.params.at(0), digest.params.at(1), digest.prefix);
}
