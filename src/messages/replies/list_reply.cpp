#include "messages/replies/list_reply.h"

list_reply::list_reply(string channel, unsigned visible, string topic, string prefix)
    : abstract_message(command, prefix), channel(channel), visible(visible), topic(topic)
{

}
