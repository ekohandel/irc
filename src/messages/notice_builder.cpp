#include <memory>

#include "messages/abstract_builder.h"
#include "messages/notice.h"
#include "messages/notice_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> notice_builder::build(build_digest digest) const
{
	if (digest.command != notice::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + notice::command + " message");

	return make_unique<notice>(digest.prefix, digest.params.at(0), digest.params.at(1));
}
