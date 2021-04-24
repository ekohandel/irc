#pragma once

#include <string>

#include "messages/abstract_message.h"

class list_end_reply : public abstract_message {
	public:
		inline static const string command = "323";

		list_end_reply(string prefix={});
};
