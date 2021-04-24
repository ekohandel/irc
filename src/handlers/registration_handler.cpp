#include <iostream>
#include <memory>

#include "handlers/registration_handler.h"
#include "messages/replies/welcome_reply.h"
#include "messages/replies/yourhost_reply.h"
#include "messages/replies/created_reply.h"
#include "messages/replies/myinfo_reply.h"

using boost::interprocess::microsec_clock;

shared_ptr<abstract_message> registration_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() == welcome_reply::command) {
        sem.post();
        return nullptr;
    }

    if (message->get_command() == created_reply::command) {
        sem.post();
        return nullptr;
    }

    if (message->get_command() == myinfo_reply::command) {
        sem.post();
        return nullptr;
    }

    if (message->get_command() == yourhost_reply::command) {
        sem.post();
        return nullptr;
    }

    return abstract_handler::handle(message);
}

void registration_handler::wait()
{
    auto deadline = microsec_clock::universal_time() + wait_time;
    for (auto i = 0 ; i < 4; i++) {
        if (!sem.timed_wait(deadline)) {
            return;
        }
    }
}