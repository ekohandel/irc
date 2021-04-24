#pragma once

#include <string>
#include <vector>

#include "messages/abstract_message.h"

using namespace std;

class list_command : public abstract_message {
	public:
		inline static const string command = "LIST";
		vector<string> channels;
		string target;

		list_command(vector<string> channels={}, string target={}, string prefix={});

		string serialize() const override;
};
