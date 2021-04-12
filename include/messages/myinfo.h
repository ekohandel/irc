#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class myinfo : public abstract_message {
	public:
		inline static const string command = "004";
		string nickname;
		string message;

		myinfo(string prefix, string nickname, string message);
		string serialize() const override;
		string get_command() const override;
};