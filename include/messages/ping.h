#pragma once

#include <vector>
#include <stdexcept>

#include "messages/abstract_message.h"

using std::vector;
using std::string;

class ping : public abstract_message {
	public:
		inline static const string command = "PING";
		vector<string> servers;

		ping(string prefix, vector<string> servers);
		ping(vector<string> servers);
		string serialize() const override;
		string get_command() const override;
};