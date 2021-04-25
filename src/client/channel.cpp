#include "client/channel.h"
#include "messages/commands/join_command.h"
#include "messages/commands/privmsg_command.h"
#include "handlers/private_message_handler.h"
#include "handlers/join_handler.h"

using namespace std;

channel::channel(string name, abstract_client &client)
    : name(name), client(client)
{
}

void channel::join(function<void(string)> notifier)
{
    handler = make_shared<join_handler>();

    client.add_handler(make_shared<private_message_handler>(notifier))
        ->add_handler(handler);

    client.send_message(make_shared<join_command>(vector<string>{name}));

    handler->wait();
}

void channel::write(string text, string target)
{
    if (target.empty())
        target = name;
    client.send_message(make_shared<privmsg_command>(target, text));
}

void channel::leave()
{
}
