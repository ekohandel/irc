#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class myinfo_reply : public abstract_message {
	public:
		inline static const string command = "004";
		string nickname;
		string message;

		myinfo_reply(string nickname, string message, string prefix={});
		string serialize() const override;
};
