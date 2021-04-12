#include <memory>

#include "messages/abstract_builder.h"
#include "messages/welcome.h"
#include "messages/welcome_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> welcome_builder::build(build_digest digest) const
{
	if (digest.command != welcome::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + welcome::command + " message");

	return make_unique<welcome>(digest.prefix, digest.params.at(0), digest.params.at(1));
}
