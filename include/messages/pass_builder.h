#pragma once

#include "messages/abstract_builder.h"
#include "messages/ping.h"

class pass_builder : public abstract_builder{
	virtual unique_ptr<abstract_message> build(build_digest digest) const;
};
