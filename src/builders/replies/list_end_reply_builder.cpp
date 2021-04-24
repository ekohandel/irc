#include "builders/replies/list_end_reply_builder.h"
#include "messages/replies/list_end_reply.h"

unique_ptr<abstract_message> list_end_reply_builder::build(build_digest digest) const
{
    if (digest.command != list_end_reply::command)
        return abstract_builder::build(digest);

    if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + list_end_reply::command + " message");

	return make_unique<list_end_reply>(digest.prefix);
}
