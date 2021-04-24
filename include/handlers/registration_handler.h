#pragma once

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include "handlers/abstract_handler.h"

using namespace std;
using boost::interprocess::interprocess_semaphore;

class registration_handler : public abstract_handler {
    public:
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;
        void wait() override;

    private:
        string message_of_the_day;
        interprocess_semaphore sem {0};
};
