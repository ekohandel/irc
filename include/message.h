#pragma once

#include <string>
#include <vector>
#include <stdexcept>

using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;

class build_digest {
	public:
		string prefix;
		string command;
		vector<string> params;
		build_digest(string text) {
			size_t position = 0;

			if (text.size() > 0 && text.at(position) == ':') {
				position = 1;
				auto prefix_end = text.find_first_of(' ');
				if (prefix_end == string::npos) {
					prefix = text.substr(position);
					position = string::npos;
				} else {
					prefix = text.substr(position, prefix_end - position);
					position = prefix_end + 1;
				}
			}

			if (position < text.size()) {
				auto command_end = text.find_first_of(' ', position);
				if (command_end == string::npos) {
					command = text.substr(position);
					position = string::npos;
				} else {
					command = text.substr(position, command_end - position);
					position = command_end + 1;
				}
			}
			if (command.size() < 1)
				throw std::invalid_argument(string{"Malformed message: "} + text);

			while (position < text.size()) {
				auto param_end = text.find_first_of(" :", position);
				if (param_end == string::npos) {
					params.push_back(text.substr(position, param_end - position));
					return;
				} else {
					switch (text.at(param_end)) {
						case ':':
							params.push_back(text.substr(param_end + 1));
							return;
							break;
						case ' ':
							params.push_back(text.substr(position, param_end - position));
							position = param_end + 1;
							break;
					}
				}
			}
		}
};

class message {
	public:
		string prefix;

		message(string prefix="") : prefix(prefix) {}
		virtual ~message() {}
		virtual string serialize() const {
			string serialized;
			if (!prefix.empty())
				serialized += string{':'} + prefix + " ";
			return serialized;
		}
};

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

class builder {
	public:
		virtual ~builder() {}
		virtual builder *set_next(builder *delegate) = 0;
		virtual unique_ptr<message> build(string text) const = 0;
};


class abstract_builder : public builder {
	private:
		builder *next_builder = nullptr;
	public:
		~abstract_builder() {
			delete next_builder;
		}
		builder *set_next(builder *delegate) override {
			next_builder = delegate;
			return delegate;
		}
		unique_ptr<message> build(string text) const override {
			if (next_builder)
				return next_builder->build(text);
			throw std::invalid_argument(
				"Unsupported message type: " + text);
		}
};

template<typename T>
class template_builder : public abstract_builder {
	public:
		unique_ptr<message> build(string text) const override {
			build_digest digest(text);
			if (digest.command != T::command)
				return abstract_builder::build(text);

			return make_unique<T>(digest);
		}
};