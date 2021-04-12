#include <iostream>
#include <memory>

#include "handlers/list_handler.h"
#include "messages/list.h"

using std::static_pointer_cast;

list_handler::list_handler()
{
    list_mutex.lock();
}

shared_ptr<abstract_message> list_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() == list_channel_end::command) {
        list_mutex.unlock();
        return nullptr;
    }

    if (message->get_command() == list_channel::command) {
        auto list_message = static_pointer_cast<list_channel>(message);
        channels.push_back(list_message->channel);
        return nullptr;
    }

    return abstract_handler::handle(message);
}

void list_handler::wait()
{
    list_mutex.lock();
}
