#include <stdexcept>

#include "handlers/abstract_handler.h"

abstract_handler::~abstract_handler()
{
    delete next_handler;
}

abstract_handler *abstract_handler::add_handler(abstract_handler *handler)
{
    if (next_handler)
        return next_handler->add_handler(handler);
    else
        next_handler = handler;

    return handler;
}

abstract_message *abstract_handler::handle(abstract_message *message) const
{
    if (next_handler)
        return next_handler->handle(message);

    throw std::invalid_argument("No handler found: " + message->serialize());
};
