#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class yourhost : public abstract_message {
	public:
		inline static const string command = "002";
		string nickname;
		string message;

		yourhost(string prefix, string nickname, string message);
		string serialize() const override;
		string get_command() const override;
};