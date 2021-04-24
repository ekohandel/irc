#include "builders/replies/list_reply_builder.h"
#include "messages/replies/list_reply.h"

unique_ptr<abstract_message> list_reply_builder::build(build_digest digest) const
{
    if (digest.command != list_reply::command)
        return abstract_builder::build(digest);

    if (digest.params.size() != 4)
		throw std::invalid_argument(string{"Malformed "} + list_reply::command + " message");

	return make_unique<list_reply>(digest.params.at(1), std::stoi(digest.params.at(2)), digest.params.at(3), digest.prefix);
}
