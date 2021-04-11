#include <memory>
#include <vector>
#include <string>

#include "messages/abstract_builder.h"

using std::unique_ptr;
using std::vector;
using std::string;

abstract_builder::~abstract_builder()
{
	delete next_builder;
}

abstract_builder *abstract_builder::add_builder(abstract_builder *builder)
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

	throw std::invalid_argument("Unsupported message type: " + digest.command);
}