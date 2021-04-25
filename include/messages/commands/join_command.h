#pragma once

#include <string>
#include <vector>

#include "messages/abstract_message.h"

using namespace std;

class join_command : public abstract_message {
	public:
		inline static const string command = "JOIN";
		vector<string> channels;
		vector<string> keys;

		join_command(vector<string> channels, vector<string> keys={}, string prefix={});

		string serialize() const override;
};
