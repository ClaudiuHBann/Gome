#include "Gome/pch.h"
//
#include "TCPServerRaw.h"
//

namespace Networking::Server
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

void TCPServerRaw::Start(CallbackAccept callback)
{
    Accept(move(callback));
}

void TCPServerRaw::Accept(CallbackAccept callback)
{
    auto self(shared_from_this());

    auto socket = make_shared<tcp::socket>(mContext.CreateSocket());
    mAcceptor->async_accept(*socket, [self, socket, callbackInst1 = move(callback)](auto ec) {
        if (!ec)
        {
            callbackInst1(make_shared<TCPClient>(move(*socket)));
        }

        self->Accept(move(callbackInst1));
    });
}
} // namespace Networking::Server
