#pragma once

#include "handlers/abstract_handler.h"

class ping_handler : public abstract_handler {
    public:
        virtual abstract_message *handle(abstract_message *message) const override;
};
