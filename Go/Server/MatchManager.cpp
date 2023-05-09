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
    TRACE("Send to every player it's color and the match rules...");
    for (size_t i = 0; i < mClients.size(); i++)
    {
        ContextServerInit context(mMatch.mRules, GetPlayerByClient(mClients[i]).GetColor());
        json contextJSON;
        context.to_json(contextJSON, context);
        auto &&contextJSONString = contextJSON.dump();

        TCPClient::bytes data((byte *)contextJSONString.data(),
                              (byte *)contextJSONString.data() + contextJSONString.size());
        mClients[i]->Send(data, HeaderMetadata::Type::TEXT,
                          [this, i = i](const auto &, const auto &) { ProcessPlayer(mClients[i]); });
    }
}

void MatchManager::ProcessPlayer(shared_ptr<TCPClient> client)
{
    client->Receive([&](auto ec, shared_ptr<MessageManager::MessageDisassembled> messageDisassembled) {
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

    string jsonString((char *)bytes.data(), (char *)bytes.data() + bytes.size());
    ContextClient contextRequest(Coord{0, 0}, Player::Joker::NONE);
    contextRequest.from_json(jsonString, contextRequest);

    scoped_lock lock(*mMutexPlayerCurrent);

    // not his turn
    if (player != mMatch.GetPlayerCurrent())
    {
        TRACE(format("\033[1;{}mPlayer\033[0m tried to make a move when it wasn't his turn...",
                     to_string((int)player.GetColor()))
                  .c_str());
        return CreateResponse(contextRequest, Error::TURN);
    }

    // has a joker active but could not activate on server side (it's already used)
    if (contextRequest.joker != Player::Joker::NONE && !player.SetActiveJoker(contextRequest.joker))
    {
        TRACE(format("\033[1;{}mPlayer\033[0m tried to use Joker::{} twice...", to_string((int)player.GetColor()),
                     Player::GetJokerName(contextRequest.joker))
                  .c_str());
        return CreateResponse(contextRequest, Error::JOKER);
    }

    // could not add the stone
    if (!mMatch.mBoard.AddStone(player, contextRequest.stone))
    {
        TRACE(vformat("\033[1;{}mPlayer\033[0m could not place stone({{ {}, {} }})...",
                      make_format_args((int)contextRequest.stone.GetPosition().GetXY().first,
                                       (int)contextRequest.stone.GetPosition().GetXY().second))
                  .c_str());
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
    auto &&contextResponseJSONString = contextResponseJSON.dump();

    TCPClient::bytes data((byte *)contextResponseJSONString.data(),
                          (byte *)contextResponseJSONString.data() + contextResponseJSONString.size());
    return Networking::Message::MessageManager::ToMessage(data, Networking::Message::HeaderMetadata::Type::TEXT);
}
} // namespace Server
