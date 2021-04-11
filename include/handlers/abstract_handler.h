#pragma once

#include <memory>

#include "messages/abstract_message.h"

using std::shared_ptr;

class abstract_handler {
    public:
        virtual ~abstract_handler() = default;
        shared_ptr<abstract_handler> add_handler(shared_ptr<abstract_handler> handler);
        virtual abstract_message *handle(abstract_message *message) const;

    private:
        shared_ptr<abstract_handler> next_handler = nullptr;
};
