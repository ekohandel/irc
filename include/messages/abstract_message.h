#pragma once

#include <string>

using std::string;

class abstract_message {
	public:
		abstract_message(string prefix);
		virtual ~abstract_message();
		virtual string serialize() const;
		virtual string get_command() const = 0;

    private:
		string prefix;
};
