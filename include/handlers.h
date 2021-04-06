#pragma once

#include "handler.h"
#include "messages.h"

class ping_handler : public abstract_handler {
    public:
        void handle(message *msg, Client &c) const override {

            ping *ping_message = dynamic_cast<ping*>(msg);
            if (ping_message) {
                unique_ptr<message> reply = make_unique<pong>(ping_message->servers);
                c.send_message(reply);
            } else
                abstract_handler::handle(msg, c);
        }
};
