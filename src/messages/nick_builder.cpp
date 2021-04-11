#include <memory>

#include "messages/abstract_builder.h"
#include "messages/nick.h"
#include "messages/nick_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> nick_builder::build(build_digest digest) const
{
	if (digest.command != nick::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 1)
		throw std::invalid_argument(string{"Malformed "} + nick::command + " message");

	return make_unique<nick>(digest.prefix, digest.params.at(0));
}
