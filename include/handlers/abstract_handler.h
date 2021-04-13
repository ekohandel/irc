#pragma once

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <memory>

#include "messages/abstract_message.h"

using std::shared_ptr;
using boost::posix_time::seconds;

class abstract_handler {
    public:
        virtual ~abstract_handler() = default;
        shared_ptr<abstract_handler> add_handler(shared_ptr<abstract_handler> handler);
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message);
        virtual void wait();

    protected:
        seconds wait_time {10};

    private:
        shared_ptr<abstract_handler> next_handler = nullptr;
};
