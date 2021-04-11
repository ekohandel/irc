#include "client/client.h"

using std::make_unique;
using std::make_shared;

client::client(string host, string service)
    : host(host), service(service)
{
}

client::~client()
{
    if (runner)
        runner->join();
}

shared_ptr<abstract_handler> client::add_handler(shared_ptr<abstract_handler> delegate)
{
    if (message_handler)
        return message_handler->add_handler(delegate);
    message_handler = delegate;
    return message_handler;
}

shared_ptr<abstract_builder> client::add_builder(shared_ptr<abstract_builder> delegate)
{
    if (message_builder)
        return message_builder->add_builder(delegate);
    message_builder = delegate;
    return message_builder;
}


void client::connect(string user_name, string real_name)
{
    user_name = user_name;
    real_name = real_name;

    tcp::resolver resolver(executer);

    auto endpoints = resolver.resolve(host, service);
    socket = make_unique<tcp::socket>(executer);

    boost::asio::async_connect(*socket, endpoints,
        [this, user_name, real_name](boost::system::error_code ec, tcp::endpoint)
        {
            if (ec)
                socket->close();
            else {
                do_read();
                send_message(make_shared<pass>("password"));
                send_message(make_shared<nick>(user_name));
                send_message(make_shared<user>(user_name, real_name));
            }
        }
    );

    start_runner();
}

void client::disconnect()
{
    executer.stop();
    socket->close();
}

void client::start_runner()
{
    runner = std::make_unique<std::thread>(
        [this]() {
            executer.run();
        }
    );
}

void client::do_read()
{
    boost::asio::async_read_until(*socket,
        read_buffer, message_delimiter,
        [this](boost::system::error_code ec, std::size_t size) {
            if (ec)
                socket->close();
            else {
                std::istream reader(&read_buffer);
                std::vector<char> text(size);
                reader.read(text.data(), size);

                do_read();

                try {
                    shared_ptr<abstract_message> message = message_builder->build(string{text.begin(), text.end() - strlen(message_delimiter)});
                    auto reply = message_handler->handle(message);
                    if (reply)
                        send_message(reply);
                } catch (std::invalid_argument e) {
                    std::cerr << e.what() << std::endl;
                }
            }
        });
}

void client::do_write()
{
    string msg = write_messages.front();

    std::cout << "Sending: " << msg << std::endl;

    boost::asio::async_write(*socket,
        boost::asio::buffer(msg, msg.length()),
        [this](boost::system::error_code ec, std::size_t)
        {
            if (ec)
                socket->close();
            else {
                write_messages.pop_front();
                if (!write_messages.empty())
                    do_write();
            }
        }
    );
}

void client::send_message(shared_ptr<abstract_message> message)
{
    auto text = message->serialize().append(message_delimiter);
    auto initiate_write = write_messages.empty();
    write_messages.push_back(text);
    if (initiate_write)
        do_write();
}
