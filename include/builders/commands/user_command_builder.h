#pragma once

#include "builders/abstract_builder.h"

class user_command_builder : public abstract_builder{
	virtual unique_ptr<abstract_message> build(build_digest digest) const;
};
