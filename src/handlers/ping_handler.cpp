#include <memory>

#include "handlers/ping_handler.h"
#include "messages/pong.h"
#include "messages/ping.h"

using std::make_shared;

shared_ptr<abstract_message> ping_handler::handle(shared_ptr<abstract_message> message) const
{
    if (message->get_command() != ping::command)
        return abstract_handler::handle(message);

    auto ping_message = std::static_pointer_cast<ping>(message);
    return make_shared<pong>(ping_message->servers);
}
