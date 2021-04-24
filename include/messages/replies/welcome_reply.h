#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class welcome_reply : public abstract_message {
	public:
		inline static const string command = "001";
		string nickname;
		string message;

		welcome_reply(string nickname, string message, string prefix={});

		string serialize() const override;
};
