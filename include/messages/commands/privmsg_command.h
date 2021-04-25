#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class privmsg_command : public abstract_message {
	public:
		inline static const string command = "PRIVMSG";
		string target;
		string text;

		privmsg_command(string target, string text, string prefix={});

		string serialize() const override;
};
