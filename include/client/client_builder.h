#pragma once

#include <memory>
#include <string>

#include "client/client.h"

using std::string;
using std::unique_ptr;

class client_builder {
    public:
        static unique_ptr<client> build(string host, string service);
};