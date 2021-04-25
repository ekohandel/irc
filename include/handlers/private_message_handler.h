#pragma once

#include "handlers/abstract_handler.h"

using namespace std;

class private_message_handler : public abstract_handler {
    public:
        private_message_handler(function<void(string)> notifier);
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;

    private:
        function<void(string)> notifier;
};
