#pragma once

#include <string>

#include "messages/abstract_message.h"

class nick : public abstract_message {
	public:
		inline static const string command = "NICK";
		string nickname;

		nick(string prefix, string nickname);
		nick(string nickname);
		string serialize() const override;
		string get_command() const override;
};
