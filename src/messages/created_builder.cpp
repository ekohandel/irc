#include <memory>

#include "messages/abstract_builder.h"
#include "messages/created.h"
#include "messages/created_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> created_builder::build(build_digest digest) const
{
	if (digest.command != created::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + created::command + " message");

	return make_unique<created>(digest.prefix, digest.params.at(0), digest.params.at(1));
}
