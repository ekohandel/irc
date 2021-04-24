#include <memory>

#include "handlers/notice_handler.h"
#include "messages/commands/notice_command.h"

using std::make_shared;

shared_ptr<abstract_message> notice_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() != notice_command::command)
        return abstract_handler::handle(message);

    auto notice_message = std::static_pointer_cast<notice_command>(message);

    return nullptr;
}
