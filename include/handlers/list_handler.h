#pragma once

#include <memory>
#include <vector>

#include "handlers/abstract_handler.h"

using namespace std;
using boost::interprocess::interprocess_semaphore;

class list_handler : public abstract_handler {
    public:
        vector<string> channels;

        virtual std::shared_ptr<abstract_message> handle(std::shared_ptr<abstract_message> message) override;
        void wait() override;

    private:
        interprocess_semaphore sem {0};
};
