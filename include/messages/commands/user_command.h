#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class user_command : public abstract_message {
	public:
		inline static const string command = "USER";
		unsigned mode;
		string username;
		string realname;

		user_command(string username, string realname, unsigned mode=0, string prefix={});

		string serialize() const override;
};