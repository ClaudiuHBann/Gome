#include "Gome/pch.h"
//
#include "TCPServerRaw.h"
//

namespace Shared::Networking::Server
{
using namespace Client;

TCPServerRaw::TCPServerRaw(const IOContext &context, const port_type port)
    : mContext(context), mAcceptor(make_unique<tcp::acceptor>(*mContext, tcp::endpoint(tcp::v4(), port)))
{
}

TCPServerRaw::~TCPServerRaw()
{
    mAcceptor->cancel();
    mAcceptor->close();
}

void TCPServerRaw::Start(const CallbackAccept &callback)
{
    Accept(callback);
}

void TCPServerRaw::Accept(const CallbackAccept &callback)
{
    auto self(shared_from_this());

    auto socket = make_shared<tcp::socket>(mContext.CreateSocket());
    mAcceptor->async_accept(*socket, [self, socket, callback](auto ec) {
        if (!ec)
        {
            callback(make_shared<TCPClient>(move(*socket))); // TODO: move shared_ptr object?
        }

        self->Accept(callback);
    });
}
} // namespace Shared::Networking::Server
