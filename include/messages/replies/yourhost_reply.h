#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class yourhost_reply : public abstract_message {
	public:
		inline static const string command = "002";
		string nickname;
		string message;

		yourhost_reply(string nickname, string message, string prefix={});

		string serialize() const override;
};
