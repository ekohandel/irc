#pragma once

#include <string>
#include <vector>

using namespace std;

class build_digest {
	public:
		string prefix;
		string command;
		vector<string> params;
		string text;

		build_digest(string text);
};
