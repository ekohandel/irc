#pragma once

#include <string>

#include "messages/abstract_message.h"

using std::string;

class abstract_motd : public abstract_message {
	private:
		string command;

	public:
		string nick;
		string message;

		abstract_motd(string prefix, string nick, string message, string command);
		string serialize() const override;
		string get_command() const override;
};

class motd_start : public abstract_motd {
	public:
		inline static const string command = "375";
		motd_start(string prefix, string nick, string message);
};

class motd : public abstract_motd {
	public:
		inline static const string command = "372";
		motd(string prefix, string nick, string message);
};

class motd_end : public abstract_motd {
	public:
		inline static const string command = "376";
		motd_end(string prefix, string nick, string message);
};