#include <memory>

#include "messages/abstract_builder.h"
#include "messages/myinfo.h"
#include "messages/myinfo_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> myinfo_builder::build(build_digest digest) const
{
	if (digest.command != myinfo::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 6)
		throw std::invalid_argument(string{"Malformed "} + myinfo::command + " message");

	return make_unique<myinfo>(digest.prefix, digest.params.at(0), digest.params.at(1));
}
