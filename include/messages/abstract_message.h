#pragma once

#include <string>

using namespace std;

class abstract_message {
	public:
		abstract_message(string command, string prefix={});

		string get_command() const;
		virtual string serialize() const;

		virtual ~abstract_message() = default;

    private:
		string prefix;
		string command;
};
