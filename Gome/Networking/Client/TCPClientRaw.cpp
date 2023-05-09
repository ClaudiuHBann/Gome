#include "Gome/pch.h"

#include "TCPClientRaw.h"

namespace Networking::Client
{
TCPClientRaw::TCPClientRaw(tcp::socket &&socket) : mSocket(make_unique<tcp::socket>(move(socket)))
{
}

TCPClientRaw::~TCPClientRaw()
{
    Disconnect();
}

const unique_ptr<tcp::socket> &TCPClientRaw::GetSocket() const
{
    return mSocket;
}

void TCPClientRaw::ConnectAsync(const basic_resolver_results<tcp> &endpoints, CallbackConnect callback)
{
    auto endpointsShared = make_shared<basic_resolver_results<tcp>>(endpoints);

    auto self(shared_from_this());
    async_connect(*self->GetSocket(), *endpointsShared,
                  [self, endpointsShared, callback = move(callback)](const auto &ec, const auto &ep) {
                      callback(ec, make_shared<tcp::endpoint>(ep));
                  });
}

void TCPClientRaw::SendAsync(const shared_ptr<bytes> &data, CallbackSend callback)
{
    auto self(shared_from_this());
    async_write(*self->GetSocket(), asio::buffer(*data),
                [self, data, callback = move(callback)](const auto &ec, const auto &size) { callback(ec, size); });
}

void TCPClientRaw::SendAllAsync(const shared_ptr<bytes> &data, CallbackSend callback)
{
    auto self(shared_from_this());
    async_write(*self->GetSocket(), asio::buffer(*data),
                [self, data, callback = move(callback)](const auto &ec, const auto &size) {
                    if (ec)
                    {
                        callback(ec, size);
                    }
                    else
                    {
                        self->SendShardAsync(data, size, move(callback));
                    }
                });
}

void TCPClientRaw::SendShardAsync(const shared_ptr<bytes> &data, const size_t offset, CallbackSend callback)
{
    auto self(shared_from_this());
    async_write(*self->GetSocket(), asio::buffer(data->data() + offset, data->size() - offset),
                [self, data, callback = move(callback), offset](const auto &ec, const auto &size) {
                    if (ec || !size)
                    {
                        callback(ec, offset + size);
                    }
                    else
                    {
                        self->SendShardAsync(data, offset + size, move(callback));
                    }
                });
}

void TCPClientRaw::ReceiveAsync(const shared_ptr<bytes> &data, CallbackRead callback)
{
    auto self(shared_from_this());
    async_read(*self->GetSocket(), asio::buffer(*data),
               [self, data, callback = move(callback)](const auto &ec, const auto &size) {
                   data->resize(size);
                   callback(ec, data);
               });
}

void TCPClientRaw::ReceiveAllAsync(const shared_ptr<bytes> &data, CallbackRead callback)
{
    auto self(shared_from_this());
    async_read(*self->GetSocket(), asio::buffer(*data),
               [self, data, callback = move(callback)](const auto &ec, const auto &size) {
                   if (ec)
                   {
                       data->resize(size);
                       callback(ec, data);
                   }
                   else
                   {
                       self->ReceiveShardAsync(data, size, move(callback));
                   }
               });
}

void TCPClientRaw::ReceiveShardAsync(const shared_ptr<bytes> &data, const size_t offset, CallbackRead callback)
{
    auto self(shared_from_this());
    async_read(*self->GetSocket(), asio::buffer(data->data() + offset, data->size() - offset),
               [self, data, callback = move(callback), offset](const auto &ec, const auto &size) {
                   if (ec || !size)
                   {
                       data->resize(offset + size);
                       callback(ec, data);
                   }
                   else
                   {
                       self->ReceiveShardAsync(data, offset + size, move(callback));
                   }
               });
}

void TCPClientRaw::Disconnect(CallbackDisconnect callback /* = [] (auto, auto) {} */)
{
    error_code ec1, ec2;

    mSocket->shutdown(tcp::socket::shutdown_both, ec1);
    mSocket->close(ec2);

    callback(ec1, ec2);
}
} // namespace Networking::Client
