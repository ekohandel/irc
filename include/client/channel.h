#pragma once

#include <functional>
#include <string>

#include "client/abstract_client.h"
#include "handlers/abstract_handler.h"

using namespace std;

class channel {
    public:
        channel(string name, abstract_client &client);
        void join(function<void(string)> notifier);
        void write(string text, string target={});
        void leave();

        string name;
    private:
        abstract_client &client;
        shared_ptr<abstract_handler> handler;
};
