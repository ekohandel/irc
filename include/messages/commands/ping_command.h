#pragma once

#include <vector>

#include "messages/abstract_message.h"

using namespace std;

class ping_command : public abstract_message {
	public:
		inline static const string command = "PING";
		vector<string> servers;

		ping_command(vector<string> servers, string prefix={});

		string serialize() const override;
};