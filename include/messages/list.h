#pragma once

#include <string>
#include <vector>

#include "messages/abstract_message.h"
#include "messages/abstract_builder.h"

using std::string;
using std::vector;

class list : public abstract_message {
	public:
		inline static const string command = "LIST";
		vector<string> channels;
		string target;

		list(string prefix, vector<string> channels={}, string target={});
		string serialize() const override;
		string get_command() const override;
};

class list_channel : public abstract_message {
	public:
		inline static const string command = "322";
		string channel;
		unsigned visible;
		string topic;

		list_channel(string prefix, string channel, unsigned visible, string topic={});
		string get_command() const override;
};

class list_channel_builder : public abstract_builder {
	virtual unique_ptr<abstract_message> build(build_digest digest) const;
};

class list_channel_end : public abstract_message {
	public:
		inline static const string command = "323";

		list_channel_end(string prefix);
		string get_command() const override;
};

class list_channel_end_builder : public abstract_builder {
	virtual unique_ptr<abstract_message> build(build_digest digest) const;
};
