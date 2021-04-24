#pragma once

#include <vector>
#include <string>

#include "messages/abstract_message.h"

using namespace std;

class pong_command : public abstract_message {
	public:
		inline static const string command = "PONG";
		vector<string> servers;

		pong_command(vector<string> servers, string prefix={});

		string serialize() const override;
};