#include <memory>

#include "messages/abstract_builder.h"
#include "messages/motd.h"
#include "messages/motd_builder.h"

using std::unique_ptr;
using std::make_unique;

unique_ptr<abstract_message> motd_start_builder::build(build_digest digest) const
{
	if (digest.command != motd_start::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + motd_start::command + " message");

	return make_unique<motd_start>(digest.prefix, digest.params.at(0), digest.params.at(1));
}

unique_ptr<abstract_message> motd_builder::build(build_digest digest) const
{
	if (digest.command != motd::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + motd::command + " message");

	return make_unique<motd>(digest.prefix, digest.params.at(0), digest.params.at(1));
}

unique_ptr<abstract_message> motd_end_builder::build(build_digest digest) const
{
	if (digest.command != motd_end::command)
		return abstract_builder::build(digest);

	if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + motd_end::command + " message");

	return make_unique<motd_end>(digest.prefix, digest.params.at(0), digest.params.at(1));
}
