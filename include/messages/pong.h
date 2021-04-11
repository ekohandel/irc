#pragma once

#include <vector>
#include <string>

#include "messages/abstract_message.h"

using std::vector;
using std::string;

class pong : public abstract_message {
	public:
		inline static const string command = "PONG";
		vector<string> servers;

		pong(string prefix, vector<string> servers);
		pong(vector<string> servers);
		string serialize() const override;
		string get_command() const override;
};