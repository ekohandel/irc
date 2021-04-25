#include <iostream>
#include <memory>

#include "handlers/join_handler.h"
#include "messages/commands/join_command.h"

using boost::interprocess::microsec_clock;

shared_ptr<abstract_message> join_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() == join_command::command) {
        sem.post();
        return nullptr;
    }

    return abstract_handler::handle(message);
}

void join_handler::wait()
{
    auto deadline = microsec_clock::universal_time() + wait_time;
    sem.timed_wait(deadline);
}
