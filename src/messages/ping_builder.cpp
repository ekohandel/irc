#include <memory>

#include "messages/abstract_builder.h"
#include "messages/ping.h"
#include "messages/ping_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> ping_builder::build(build_digest digest) const
{
	if (digest.command != ping::command)
		return abstract_builder::build(digest);

	if (digest.params.size() == 0)
		throw std::invalid_argument(string{"Malformed "} + ping::command + " message");

	return make_unique<ping>(digest.prefix, digest.params);
}
