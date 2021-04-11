#include "client/client_builder.h"
#include "messages/motd_builder.h"
#include "messages/nick_builder.h"
#include "messages/pass_builder.h"
#include "messages/ping_builder.h"
#include "messages/pong_builder.h"
#include "messages/user_builder.h"
#include "messages/notice_builder.h"

#include "handlers/ping_handler.h"
#include "handlers/motd_handler.h"
#include "handlers/notice_handler.h"

using std::make_unique;
using std::make_shared;

unique_ptr<client> client_builder::build(string host, string service)
{
    auto c = make_unique<client>(host, service);

    (c->add_builder(make_shared<pass_builder>()))
        ->add_builder(make_shared<nick_builder>())
        ->add_builder(make_shared<user_builder>())
        ->add_builder(make_shared<ping_builder>())
        ->add_builder(make_shared<pong_builder>())
        ->add_builder(make_shared<notice_builder>())
        ->add_builder(make_shared<motd_start_builder>())
        ->add_builder(make_shared<motd_builder>())
        ->add_builder(make_shared<motd_end_builder>())
    ;

    (c->add_handler(make_shared<ping_handler>()))
        ->add_handler(make_shared<motd_handler>())
        ->add_handler(make_shared<notice_handler>())
    ;

    return c;
}
