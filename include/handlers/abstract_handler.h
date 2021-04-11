#pragma once

#include <memory>

#include "messages/abstract_message.h"

using std::shared_ptr;

class abstract_handler {
    public:
        virtual ~abstract_handler() = default;
        shared_ptr<abstract_handler> add_handler(shared_ptr<abstract_handler> handler);
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message);

    private:
        shared_ptr<abstract_handler> next_handler = nullptr;
};
