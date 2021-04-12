#include <boost/algorithm/string/join.hpp>
#include <string>

#include "messages/list.h"
#include "messages/abstract_message.h"
#include "messages/abstract_builder.h"

using std::string;

list::list(string prefix, vector<string> channels, string target)
	: abstract_message(prefix), channels(channels), target(target)
{
}

string list::serialize() const
{
    string serialized = abstract_message::serialize() + command;

    serialized += boost::algorithm::join(channels, ",");

    if (target.size())
        serialized += " " + target;

    return serialized;
}

string list::get_command() const
{
	return command;
}


list_channel::list_channel(string prefix, string channel, unsigned visible, string topic)
    : abstract_message(prefix), channel(channel), visible(visible), topic(topic)
{
}

string list_channel::get_command() const
{
    return command;
}

unique_ptr<abstract_message> list_channel_builder::build(build_digest digest) const
{
    if (digest.command != list_channel::command)
        return abstract_builder::build(digest);

    if (digest.params.size() != 4)
		throw std::invalid_argument(string{"Malformed "} + list_channel::command + " message");

	return make_unique<list_channel>(digest.prefix, digest.params.at(1), std::stoi(digest.params.at(2)), digest.params.at(3));
}

list_channel_end::list_channel_end(string prefix)
    : abstract_message(prefix)
{
}

string list_channel_end::get_command() const
{
    return command;
}

unique_ptr<abstract_message> list_channel_end_builder::build(build_digest digest) const
{
    if (digest.command != list_channel_end::command)
        return abstract_builder::build(digest);

    if (digest.params.size() != 2)
		throw std::invalid_argument(string{"Malformed "} + list_channel_end::command + " message");

	return make_unique<list_channel_end>(digest.prefix);
}
