#pragma once

#include "message.h"

class pass : public message {
	public:
		static constexpr char command[] = "PASS";
		string password;

		pass(string prefix, string password)
			: message(prefix), password(password) {}
		pass(string password)
			: pass("", password) {}
		pass(build_digest digest)
			: pass(digest.prefix, digest.params.at(0)) {
			if (digest.params.size() != 1)
				throw std::invalid_argument(string{"Malformed "} + command + " message");
		}
		string serialize() const override {
			return message::serialize() + command + " " + password;
		}
};

class nick : public message {
	public:
		static constexpr char command[] = "NICK";
		string nickname;

		nick(string prefix, string nickname)
			: message(prefix), nickname(nickname) {}
		nick(string nickname)
			: nick("", nickname) {}
		nick(build_digest digest)
			: nick(digest.prefix, digest.params.at(0)) {
			if (digest.params.size() != 1)
				throw std::invalid_argument(string{"Malformed "} + command + " message");
		}
		string serialize() const override {
			return message::serialize() + command + " " + nickname;
		}
};

class user : public message {
	public:
		static constexpr char command[] = "USER";
		unsigned mode;
		string username;
		string realname;

		user(string prefix, string username, string realname, unsigned mode=0)
			: message(prefix), username(username), realname(realname), mode(mode) {}
		user(string username, string realname, unsigned mode=0)
			:user("", username, realname, mode) {}
		user(build_digest digest)
			: user(digest.prefix, digest.params.at(0), digest.params.at(3)) {
			if (digest.params.size() != 4)
				throw std::invalid_argument(string{"Malformed "} + command + " message");
		}
		string serialize() const override {
			string serialized = message::serialize() + command + " " + username + " " + std::to_string(mode) + " * ";
			if (string::npos != realname.find_first_of(' '))
				serialized += ":";
			return serialized + realname;
		}
};

class ping : public message {
	public:
		static constexpr char command[] = "PING";
		vector<string> servers;

		ping(string prefix, vector<string> servers)
			: message(prefix), servers(servers) {
			if (servers.empty())
				throw std::invalid_argument(string{"Malformed "} + command + " message");
		}
		ping(vector<string> servers)
			: ping("", servers) {}
		ping(build_digest digest)
			: ping(digest.prefix, digest.params) {}
		string serialize() const override {
			string serialized = message::serialize() + command;
			for (auto server: servers)
				serialized += " " + server;
			return serialized;
		}
};

class pong : public message {
	public:
		static constexpr char command[] = "PONG";
		vector<string> servers;

		pong(string prefix, vector<string> servers)
			: message(prefix), servers(servers) {
			if (servers.empty())
				throw std::invalid_argument(string{"Malformed "} + command + " message");
		}
		pong(vector<string> servers)
			: pong("", servers) {}
		pong(build_digest digest)
			: pong(digest.prefix, digest.params) {}
		string serialize() const override {
			string serialized = message::serialize() + command;
			for (auto server: servers)
				serialized += " " + server;
			return serialized;
		}
};

class notice: public message
{
	public:
		static constexpr char command[] = "NOTICE";
		string message_target;
		string text;

		notice(string prefix, string message_target, string text)
			: message(prefix), message_target(message_target), text(text) {}
		notice(string message_target, string text)
			: notice("", message_target, text) {}
		notice(build_digest digest)
			: notice(digest.prefix, digest.params.at(0), digest.params.at(1)) {}
		string serialize() const override {
			return message::serialize() + command + " " + message_target + " " + text;
		}
};