#pragma once

#include <mutex>
#include <vector>

#include "handlers/abstract_handler.h"

using std::mutex;
using std::vector;

class list_handler : public abstract_handler {
    private:
        mutex list_mutex;

    public:
        vector<string> channels;

        list_handler();
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;
        void wait() override;
};