#include <memory>

#include "messages/abstract_builder.h"
#include "messages/yourhost.h"
#include "messages/yourhost_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> yourhost_builder::build(build_digest digest) const
{
	if (digest.command != yourhost::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + yourhost::command + " message");

	return make_unique<yourhost>(digest.prefix, digest.params.at(0), digest.params.at(1));
}
