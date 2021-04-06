#pragma once

#include <memory>

#include "message.h"
#include "client.h"

using std::unique_ptr;

class Client;

class handler {
    public:
        virtual ~handler() {}
        virtual handler *add_handler(handler *delegate) = 0;
        virtual void handle(message *msg, Client &c) const = 0;
};

class abstract_handler : public handler {
    private:
        handler *next_handler = nullptr;
    public:
        ~abstract_handler() {
            delete next_handler;
        }
        handler *add_handler(handler *delegate) override {
            if (next_handler)
                return next_handler->add_handler(delegate);
            else
                next_handler = delegate;

            return delegate;
        }
        void handle(message *msg, Client &c) const override {
            if (next_handler) {
                next_handler->handle(msg, c);
                return;
            }
            throw std::invalid_argument("No handler found: " + msg->serialize());
        }
};
