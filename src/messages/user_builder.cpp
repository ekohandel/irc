#include <memory>

#include "messages/abstract_builder.h"
#include "messages/user.h"
#include "messages/user_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> user_builder::build(build_digest digest) const
{
	if (digest.command != user::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 4)
		throw std::invalid_argument(string{"Malformed "} + user::command + " message");

	return make_unique<user>(digest.prefix, digest.params.at(0), digest.params.at(3));
}
