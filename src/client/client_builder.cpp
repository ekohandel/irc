#include "client/client_builder.h"
#include "messages/nick_builder.h"
#include "messages/pass_builder.h"
#include "messages/ping_builder.h"
#include "messages/pong_builder.h"
#include "messages/user_builder.h"
#include "handlers/ping_handler.h"

client *client_builder::build(string host, string service)
{
    client *c = new client(host, service);

    (c->add_builder(new pass_builder()))
        ->add_builder(new nick_builder())
        ->add_builder(new user_builder())
        ->add_builder(new ping_builder())
        ->add_builder(new pong_builder())
    ;

    (c->add_handler(new ping_handler()))
    ;

    return c;
}
