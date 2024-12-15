#include "Gome/pch.h"

#include "Gome/Networking/Message/MessageConverter.h"
#include "TCPClient.h"

namespace Networking::Client
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
    auto &&bytess = MessageConverter::MessageToBytes(message);
    auto bytesShared = make_shared<bytes>(move(bytess));

    mTCPClientRaw->SendAllAsync(bytesShared,
                                [bytesShared, callback = move(callback)](auto ec, auto size) { callback(ec, size); });
}

void TCPClient::Receive(CallbackRead callback)
{
    auto metadata = make_shared<bytes>(HeaderMetadata::SIZE);
    mTCPClientRaw->ReceiveAllAsync(
        metadata, [selfTCPClientRaw = mTCPClientRaw, metadata, callback = move(callback)](auto ec, auto bytess) {
            if (ec)
            {
                callback(ec, {});
            }
            else
            {
                auto &&packetMetadata = MessageConverter::BytesToPacketMetadata(*bytess);
                auto data = make_shared<bytes>(packetMetadata.GetHeaderMetadata().GetSize());
                selfTCPClientRaw->ReceiveAllAsync(
                    data, [data, bytesMetadata = bytess, callback = move(callback)](auto ec, auto bytes) {
                        if (ec)
                        {
                            callback(ec, {});
                        }
                        else
                        {
                            bytesMetadata->insert(bytesMetadata->end(), bytes->begin(), bytes->end());

                            auto &&messageBytes = MessageConverter::BytesToMessage(*bytesMetadata);
                            auto &&messageDisassembled = MessageManager::FromMessage(messageBytes);

                            callback(ec, make_shared<MessageManager::MessageDisassembled>(move(messageDisassembled)));
                        }
                    });
            }
        });
}
} // namespace Networking::Client
