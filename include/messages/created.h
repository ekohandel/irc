#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class created : public abstract_message {
	public:
		inline static const string command = "003";
		string nickname;
		string message;

		created(string prefix, string nickname, string message);
		string serialize() const override;
		string get_command() const override;
};