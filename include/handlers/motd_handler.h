#pragma once

#include "handlers/abstract_handler.h"

class motd_handler : public abstract_handler {
    private:
        string message_of_the_day;
    public:
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;
};