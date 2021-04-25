#include "handlers/private_message_handler.h"
#include "messages/commands/privmsg_command.h"

private_message_handler::private_message_handler(function<void(string)> notifier)
    : notifier(notifier)
{
}

shared_ptr<abstract_message> private_message_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() != privmsg_command::command)
        return abstract_handler::handle(message);

    auto privmsg_message = std::static_pointer_cast<privmsg_command>(message);
    notifier(privmsg_message->text);

    return nullptr;
}
