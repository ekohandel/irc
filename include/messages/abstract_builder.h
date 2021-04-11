#pragma once

#include <memory>

#include "messages/abstract_message.h"
#include "messages/build_digest.h"

using std::unique_ptr;
using std::shared_ptr;

class abstract_builder {
	public:
		shared_ptr<abstract_builder> add_builder(shared_ptr<abstract_builder> builder);
		virtual unique_ptr<abstract_message> build(build_digest digest) const;

	private:
		shared_ptr<abstract_builder> next_builder = nullptr;
};
