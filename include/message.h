#pragma once

#include <memory>
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

class builder {
	public:
		virtual ~builder() {}
		virtual builder *add_builder(builder *delegate) = 0;
		virtual unique_ptr<message> build(string text) const = 0;
};


class abstract_builder : public builder {
	private:
		builder *next_builder = nullptr;
	public:
		~abstract_builder() {
			delete next_builder;
		}
		builder *add_builder(builder *delegate) override {
			if (next_builder)
				return next_builder->add_builder(delegate);
			else
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