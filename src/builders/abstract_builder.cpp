#include <memory>
#include <vector>
#include <string>

#include "builders/abstract_builder.h"

using std::unique_ptr;
using std::shared_ptr;
using std::vector;
using std::string;

shared_ptr<abstract_builder> abstract_builder::add_builder(shared_ptr<abstract_builder> builder)
{
	if (next_builder)
		return next_builder->add_builder(builder);
	else
		next_builder = builder;

	return next_builder;
}

unique_ptr<abstract_message> abstract_builder::build(build_digest digest) const
{
	if (next_builder)
		return next_builder->build(digest);

	throw std::invalid_argument("Unsupported message: " + digest.text);
}
