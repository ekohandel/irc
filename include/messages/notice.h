#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class notice : public abstract_message {
	public:
		inline static const string command = "NOTICE";
		string target;
		string text;

		notice(string prefix, string target, string text);
		string serialize() const override;
		string get_command() const override;
};