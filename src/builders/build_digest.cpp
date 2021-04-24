#include <string>
#include <vector>
#include <stdexcept>

#include "builders/build_digest.h"

using std::string;
using std::vector;

build_digest::build_digest(string text)
	: text(text)
{
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
