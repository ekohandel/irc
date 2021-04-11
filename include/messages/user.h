#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class user : public abstract_message {
	public:
		inline static const string command = "USER";
		unsigned mode;
		string username;
		string realname;

		user(string prefix, string username, string realname, unsigned mode=0);
		user(string username, string realname, unsigned mode=0);
		string serialize() const override;
		string get_command() const override;
};