#pragma once

#include "messages/abstract_message.h"

class abstract_handler {
    public:
        ~abstract_handler();
        abstract_handler *add_handler(abstract_handler *handler);
        virtual abstract_message *handle(abstract_message *message) const;

    private:
        abstract_handler *next_handler = nullptr;
};
