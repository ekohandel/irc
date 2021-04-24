#pragma once

#include "handlers/abstract_handler.h"

using namespace std;

class notice_handler : public abstract_handler {
    public:
        virtual shared_ptr<abstract_message> handle(shared_ptr<abstract_message> message) override;
};
