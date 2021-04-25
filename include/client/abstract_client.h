#pragma once

#include <memory>

#include "builders/abstract_builder.h"
#include "handlers/abstract_handler.h"

using namespace std;

class abstract_client : public abstract_handler, public abstract_builder {
    public:
        virtual void send_message(shared_ptr<abstract_message> message) = 0;

        virtual ~abstract_client() = default;
};