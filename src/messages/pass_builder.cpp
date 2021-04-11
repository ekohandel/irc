#include <memory>

#include "messages/abstract_builder.h"
#include "messages/pass.h"
#include "messages/pass_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> pass_builder::build(build_digest digest) const
{
	if (digest.command != pass::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 1)
		throw std::invalid_argument(string{"Malformed "} + pass::command + " message");

	return make_unique<pass>(digest.prefix, digest.params.at(0));
}
