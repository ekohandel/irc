#pragma once

#include <string>

#include "messages/abstract_message.h"

using namespace std;

class list_reply : public abstract_message {
	public:
		inline static const string command = "322";
		string channel;
		unsigned visible;
		string topic;

		list_reply(string channel, unsigned visible, string topic={}, string prefix={});
};
