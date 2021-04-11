#include <iostream>
#include <memory>

#include "handlers/motd_handler.h"
#include "messages/motd.h"

shared_ptr<abstract_message> motd_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() == motd_start::command) {
        auto msg = std::static_pointer_cast<motd_start>(message);
        message_of_the_day = msg->message;
        return nullptr;
    }

    if (message->get_command() == motd::command) {
        auto msg = std::static_pointer_cast<motd>(message);
        message_of_the_day += "\r\n" + msg->message;
        return nullptr;
    }

    if (message->get_command() == motd_end::command) {
        auto msg = std::static_pointer_cast<motd_end>(message);
        message_of_the_day += "\r\n" + msg->message;
        return nullptr;
    }

    return abstract_handler::handle(message);
}
