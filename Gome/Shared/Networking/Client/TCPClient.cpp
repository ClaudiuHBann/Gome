#include "Gome/pch.h"
//
#include "TCPClient.h"
//
#include "Gome/Shared/Networking/Message/MessageConverter.h"
#include "Gome/Shared/Networking/Message/MessageManager.h"

namespace Shared::Networking::Client
{
using namespace Message;

TCPClient::TCPClient(tcp::socket &&socket) : mTCPClientRaw(make_shared<TCPClientRaw>(move(socket)))
{
}

void TCPClient::Connect(const basic_resolver_results<tcp> &endpoints, CallbackConnect callback)
{
    mTCPClientRaw->ConnectAsync(endpoints, move(callback));
}

void TCPClient::Disconnect(CallbackDisconnect callback /* = [] (auto, auto) {} */)
{
    mTCPClientRaw->Disconnect(move(callback));
}

void TCPClient::Send(const bytes &data, const HeaderMetadata::Type type, CallbackSend callback)
{
    auto &&message = MessageManager::ToMessage(data, type);
    auto &&bytes = MessageConverter::MessageToBytes(message);
    auto bytesShared = make_shared<TCPClient::bytes>(move(bytes));

    mTCPClientRaw->SendAllAsync(
        bytesShared, [bytesShared, callbackInst1 = move(callback)](auto ec, auto size) { callbackInst1(ec, size); });
}

void TCPClient::Receive(CallbackRead callback)
{
    auto metadata = make_shared<bytes>(HeaderMetadata::SIZE);
    mTCPClientRaw->ReceiveAllAsync(
        metadata, [selfTCPClientRaw = mTCPClientRaw, metadata, callbackInst1 = move(callback)](auto ec, auto bytes) {
            if (ec)
            {
                callbackInst1(ec, {});
            }
            else
            {
                auto &&packetMetadata = MessageConverter::BytesToPacketMetadata(*bytes);
                auto data = make_shared<TCPClient::bytes>(packetMetadata.GetHeaderMetadata().GetSize());
                selfTCPClientRaw->ReceiveAllAsync(data, [data, bytesMetadata = bytes,
                                                         callbackInst2 = move(callbackInst1)](auto ec, auto bytes) {
                    if (ec)
                    {
                        callbackInst2(ec, {});
                    }
                    else
                    {
                        bytesMetadata->append_range(move(*bytes));

                        auto &&messageBytes = MessageConverter::BytesToMessage(*bytesMetadata);
                        auto &&messageDisassembled = MessageManager::FromMessage(messageBytes);

                        callbackInst2(ec, make_shared<MessageManager::MessageDisassembled>(move(messageDisassembled)));
                    }
                });
            }
        });
}
} // namespace Shared::Networking::Client
