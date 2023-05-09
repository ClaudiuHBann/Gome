#include "Gome/pch.h"

#include "TCPServerRaw.h"

namespace Networking::Server
{
using namespace Client;

TCPServerRaw::TCPServerRaw(IOContext &context, const uint16_t port)
    : mContext(context), mAcceptor(make_unique<tcp::acceptor>(*mContext, tcp::endpoint(tcp::v4(), port)))
{
}

void TCPServerRaw::Start(CallbackAccept callback)
{
    Accept(move(callback));
}

void TCPServerRaw::Accept(CallbackAccept callback)
{
    auto self(shared_from_this());

    auto socket = make_shared<tcp::socket>(mContext.CreateSocket());
    mAcceptor->async_accept(*socket, [self, socket, callback = move(callback)](const auto ec) {
        if (!ec)
        {
            callback(make_shared<TCPClient>(move(*socket)));
        }

        self->Accept(move(callback));
    });
}
} // namespace Networking::Server
