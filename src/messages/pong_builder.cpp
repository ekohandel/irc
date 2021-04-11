#include <memory>

#include "messages/abstract_builder.h"
#include "messages/pong.h"
#include "messages/pong_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> pong_builder::build(build_digest digest) const
{
	if (digest.command != pong::command)
		return abstract_builder::build(digest);

	if (digest.params.size() == 0)
		throw std::invalid_argument(string{"Malformed "} + pong::command + " message");

	return make_unique<pong>(digest.prefix, digest.params);
}
