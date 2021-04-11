#include <string>

#include "messages/abstract_message.h"

using std::string;

abstract_message::abstract_message(string prefix="")
    : prefix(prefix)
{
}

string abstract_message::serialize() const
{
    if (!prefix.empty())
        return string{':'} + prefix + " ";
    return string{};
};
