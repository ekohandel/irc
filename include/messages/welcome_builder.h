#pragma once

#include "messages/abstract_builder.h"

class welcome_builder : public abstract_builder{
	virtual unique_ptr<abstract_message> build(build_digest digest) const;
};
