#pragma once

#include "client.h"
#include "messages.h"
#include "handlers.h"

class client_builder {
    public:
        static Client *build(string host, string service) {
            Client *c = new Client(host, service);

            (c->add_builder(new template_builder<pass>()))
                ->add_builder(new template_builder<nick>())
                ->add_builder(new template_builder<user>())
                ->add_builder(new template_builder<ping>())
                ->add_builder(new template_builder<pong>())
                ->add_builder(new template_builder<notice>())
            ;

            (c->add_handler(new ping_handler()))
            ;

            return c;
        }
};