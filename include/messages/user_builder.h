#pragma once

#include "messages/abstract_builder.h"
#include "messages/user.h"

class user_builder : public abstract_builder{
	virtual unique_ptr<abstract_message> build(build_digest digest) const;
};
