#pragma once

#include <vector>

#include "handlers/abstract_handler.h"

using std::vector;
using boost::interprocess::interprocess_semaphore;

class list_handler : public abstract_handler {
    private:
        interprocess_semaphore sem {0};

    public:
        vector<string> channels;

        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;
        void wait() override;
};