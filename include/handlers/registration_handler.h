#pragma once

#include <mutex>

#include "handlers/abstract_handler.h"

using std::mutex;

class registration_handler : public abstract_handler {
    private:
        string message_of_the_day;
        mutex welcome_mutex;
        mutex created_mutex;
        mutex myinfo_mutex;
        mutex yourhost_mutex;

    public:
        registration_handler();
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;
        void wait() override;
};