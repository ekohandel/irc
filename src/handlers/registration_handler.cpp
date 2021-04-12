#include <iostream>
#include <memory>

#include "handlers/registration_handler.h"
#include "messages/welcome.h"
#include "messages/yourhost.h"
#include "messages/created.h"
#include "messages/myinfo.h"

registration_handler::registration_handler()
{
    welcome_mutex.lock();
    created_mutex.lock();
    myinfo_mutex.lock();
    yourhost_mutex.lock();
}

shared_ptr<abstract_message> registration_handler::handle(shared_ptr<abstract_message> message)
{
    if (message->get_command() == welcome::command) {
        welcome_mutex.unlock();
        return nullptr;
    }

    if (message->get_command() == created::command) {
        created_mutex.unlock();
        return nullptr;
    }

    if (message->get_command() == myinfo::command) {
        myinfo_mutex.unlock();
        return nullptr;
    }

    if (message->get_command() == yourhost::command) {
        yourhost_mutex.unlock();
        return nullptr;
    }

    return abstract_handler::handle(message);
}

void registration_handler::wait()
{
    welcome_mutex.lock();
    created_mutex.lock();
    myinfo_mutex.lock();
    yourhost_mutex.lock();
}