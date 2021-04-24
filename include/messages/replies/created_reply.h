#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class created_reply : public abstract_message {
	public:
		inline static const string command = "003";
		string nickname;
		string message;

		created_reply(string nickname, string message, string prefix={});

		string serialize() const override;
};
