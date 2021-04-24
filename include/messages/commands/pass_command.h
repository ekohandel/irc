#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class pass_command : public abstract_message {
	public:
		inline static const string command = "PASS";
		string password;

		pass_command(string password, string prefix={});

		string serialize() const override;
};