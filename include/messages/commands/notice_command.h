#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class notice_command : public abstract_message {
	public:
		inline static const string command = "NOTICE";
		string target;
		string text;

		notice_command(string target, string text, string prefix={});

		string serialize() const override;
};