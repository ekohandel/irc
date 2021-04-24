#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class nick_command : public abstract_message {
	public:
		inline static const string command = "NICK";
		string nickname;

		nick_command(string nickname, string prefix={});

		string serialize() const override;
};
