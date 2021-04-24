#include <memory>

#include "handlers/ping_handler.h"
#include "messages/commands/pong_command.h"
#include "messages/commands/ping_command.h"

using std::make_shared;

shared_ptr<abstract_message> ping_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() != ping_command::command)
        return abstract_handler::handle(message);

    auto ping_message = std::static_pointer_cast<ping_command>(message);
    return make_shared<pong_command>(ping_message->servers);
}
