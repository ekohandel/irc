#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

class build_digest {
	public:
		string prefix;
		string command;
		vector<string> params;
		string text;

		build_digest(string text);
};
