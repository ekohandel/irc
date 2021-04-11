#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class pass : public abstract_message {
	public:
		inline static const string command = "PASS";
		string password;

		pass(string prefix, string password);
		pass(string password);
		string serialize() const override;
		string get_command() const override;
};