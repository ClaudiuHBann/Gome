#include "Go/pch.h"

#include "Gome/Networking/Message/MessageConverter.h"
#include "MatchManager.h"

namespace Server
{
using namespace Networking;
using namespace Client;
using namespace Game;

MatchManager::MatchManager(const vector<shared_ptr<TCPClient>> &clients, Match &match)
    : mClients(clients), mMatch(match), mMutexPlayerCurrent(make_shared<mutex>())
{
}

void MatchManager::Process()
{
    for (size_t i = 0; i < mClients.size(); i++)
    {
        ContextServerInit context({0, Coord{0, 0}}, Player::Color::NONE);
        json contextJSON;
        context.to_json(contextJSON, context);

        mClients[i]->Send(*reinterpret_cast<TCPClient::bytes *>(contextJSON.dump().data()), HeaderMetadata::Type::TEXT,
                          [this, i = i](const auto &, const auto &) { ProcessPlayer(mClients[i]); });
    }
}

void MatchManager::ProcessPlayer(shared_ptr<TCPClient> client)
{
    client->Receive([&, match = mMatch](auto ec, shared_ptr<MessageManager::MessageDisassembled> messageDisassembled) {
        if (!ec)
        {
            auto &&message = ProcessPlayerMessage(GetPlayerByClient(client), messageDisassembled);
            auto &&messageBytes = Networking::Message::MessageConverter::MessageToBytes(message);
            client->Send(messageBytes, Networking::Message::HeaderMetadata::Type::TEXT, [](auto, auto) {});
        }

        ProcessPlayer(client);
    });
}

Player &MatchManager::GetPlayerByClient(const shared_ptr<TCPClient> &client)
{
    size_t indexOfClient = 0;
    for (; indexOfClient < mClients.size(); indexOfClient++)
    {
        if (client == mClients[indexOfClient])
        {
            break;
        }
    }

    return mMatch.mPlayers[indexOfClient];
}

Networking::Message::Message MatchManager::ProcessPlayerMessage(Player &player,
                                                                shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;

    auto &jsonString = *reinterpret_cast<string *>(bytes.data());
    ContextClient contextRequest(Coord{0, 0}, Player::Joker::NONE);
    contextRequest.from_json(jsonString, contextRequest);

    scoped_lock lock(*mMutexPlayerCurrent);

    // not his turn
    if (player != mMatch.GetPlayerCurrent())
    {
        return CreateResponse(contextRequest, Error::TURN);
    }

    // has a joker active but could not activate on server side (it's already used)
    if (contextRequest.joker != Player::Joker::NONE && !player.SetActiveJoker(contextRequest.joker))
    {
        return CreateResponse(contextRequest, Error::JOKER);
    }

    // could not add the stone
    if (!mMatch.mBoard.AddStone(player, contextRequest.stone))
    {
        return CreateResponse(contextRequest, Error::STONE);
    }

    // cycle player and respond
    mMatch.GetPlayerNext();
    return CreateResponse(contextRequest, Error::NONE);
}

Networking::Message::Message MatchManager::CreateResponse(const ContextClient &contextRequest, const Error error)
{
    string message{"All Good!"s};
    switch (error)
    {
    case Error::TURN:
        message = "Wait your turn!"s;
        break;
    case Error::JOKER:
        message = format("Joker {} is already used!", Player::GetJokerName(contextRequest.joker));
        break;
    case Error::STONE:
        message = format("Couldn't add stone!", Player::GetJokerName(contextRequest.joker));
        break;
    }

    ContextServer contextResponse(mMatch.mBoard, message);
    json contextResponseJSON;
    contextResponse.to_json(contextResponseJSON, contextResponse);

    return Networking::Message::MessageManager::ToMessage(
        *reinterpret_cast<MessageManager::bytes *>(contextResponseJSON.dump().data()),
        Networking::Message::HeaderMetadata::Type::TEXT);
}
} // namespace Server
