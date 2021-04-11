#pragma once

#include <string>

#include "client/client.h"

using std::string;

class client_builder {
    public:
        static client *build(string host, string service);
};