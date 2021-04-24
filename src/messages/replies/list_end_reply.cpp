#include "messages/replies/list_end_reply.h"

list_end_reply::list_end_reply(string prefix)
	: abstract_message(command, prefix)
{
}
