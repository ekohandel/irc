#include <iostream>
#include <memory>

#include "handlers/registration_handler.h"
#include "messages/welcome.h"
#include "messages/yourhost.h"
#include "messages/created.h"
#include "messages/myinfo.h"

using boost::interprocess::microsec_clock;

shared_ptr<abstract_message> registration_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() == welcome::command) {
        sem.post();
        return nullptr;
    }

    if (message->get_command() == created::command) {
        sem.post();
        return nullptr;
    }

    if (message->get_command() == myinfo::command) {
        sem.post();
        return nullptr;
    }

    if (message->get_command() == yourhost::command) {
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