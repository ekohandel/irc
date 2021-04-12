#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class welcome : public abstract_message {
	public:
		inline static const string command = "001";
		string nickname;
		string message;

		welcome(string prefix, string nickname, string message);
		string serialize() const override;
		string get_command() const override;
};