#pragma once

#include <memory>

#include "messages/abstract_message.h"
#include "messages/build_digest.h"

using std::unique_ptr;

class abstract_builder {
	public:
		~abstract_builder();
		abstract_builder *add_builder(abstract_builder *builder);
		virtual unique_ptr<abstract_message> build(build_digest digest) const;

	private:
		abstract_builder *next_builder = nullptr;
};
