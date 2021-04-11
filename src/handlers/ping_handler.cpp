#include "handlers/ping_handler.h"
#include "messages/pong.h"
#include "messages/ping.h"

abstract_message *ping_handler::handle(abstract_message *message) const
{
    if (message->get_command() != ping::command)
        return abstract_handler::handle(message);

    ping *ping_message = static_cast<ping*>(message);
    return new pong(ping_message->servers);
}
