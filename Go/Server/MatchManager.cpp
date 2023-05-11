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

void MatchManager::SendContextStarting(shared_ptr<TCPClient> client, function<void()> callback)
{
    // send the init context
    ContextServerInit context(mMatch.mRules, GetPlayerByClient(client).GetColor());
    auto &&contextJSONString = context.ToJSONString();

    bytes data((byte *)contextJSONString.data(), (byte *)contextJSONString.data() + contextJSONString.size());
    client->Send(data, HeaderMetadata::Type::TEXT, [this, client, callback = move(callback)](auto, auto) {
        // send the updated context
        ContextServer context(mMatch.mBoard, ContextServer::Error::NONE, "Have fun!");
        auto &&contextJSONString = context.ToJSONString();

        bytes data((byte *)contextJSONString.data(), (byte *)contextJSONString.data() + contextJSONString.size());
        client->Send(data, HeaderMetadata::Type::TEXT, [callback = move(callback)](auto, auto) { callback(); });
    });
}

void MatchManager::Process()
{
    TRACE("Send to every player it's color, the match rules and the board...");
    for (size_t i = 0; i < mClients.size(); i++)
    {
        SendContextStarting(mClients[i], [this, i]() { ProcessPlayer(mClients[i]); });
    }
}

void MatchManager::Finish()
{
    auto winner = mMatch.mBoard.GetWinner(mMatch.mPlayers);
    if (!winner.has_value())
    {
        return;
    }

    // create a response to send the winner through the message
    ContextServerUninit contextResponse(winner.value());

    // send it to every client
    auto &&json = contextResponse.ToJSONString();
    bytes jsonAsBytes((byte *)json.data(), (byte *)json.data() + json.size());

    for (const auto &client : mClients)
    {
        client->Send(jsonAsBytes, Networking::Message::HeaderMetadata::Type::TEXT,
                     [client](auto, auto) { client->Disconnect(); });
    }
}

void MatchManager::ProcessPlayer(shared_ptr<TCPClient> clientCurrent)
{
    clientCurrent->Receive([&, clientCurrent](auto ec,
                                              shared_ptr<MessageManager::MessageDisassembled> messageDisassembled) {
        if (!ec)
        {
            auto &&context = ProcessPlayerMessage(GetPlayerByClient(clientCurrent), messageDisassembled);
            auto &&jsonString = context.ToJSONString();
            bytes jsonAsBytes((byte *)jsonString.data(), (byte *)jsonString.data() + jsonString.size());

            // if eveything is good send it to everyone else to the client that made the error
            if (context.error == ContextServer::Error::NONE)
            {
                for (const auto &client : mClients)
                {
                    client->Send(jsonAsBytes, Networking::Message::HeaderMetadata::Type::TEXT, [](auto, auto) {});
                }
            }
            else
            {
                clientCurrent->Send(jsonAsBytes, Networking::Message::HeaderMetadata::Type::TEXT, [](auto, auto) {});
            }
        }

        if (!mMatch.mBoard.IsGameStateTerminal(mMatch.mPlayers))
        {
            ProcessPlayer(clientCurrent);
        }
        else
        {
            // if we place this just in the finish method it will be invoked multiple times
            auto winner = mMatch.mBoard.GetWinner(mMatch.mPlayers);
            if (winner.has_value())
            {
                TRACE(
                    format("A match has finished and the winner is {}.", Player::GetColorName(winner.value())).c_str());
                TRACE("Sending context to every client and disconnecting them...");
            }

            Finish();
        }
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

ContextServer MatchManager::ProcessPlayerMessage(Player &player,
                                                 shared_ptr<MessageManager::MessageDisassembled> message)
{
    auto &[guid, type, bytes] = *message;

    string jsonString((char *)bytes.data(), (char *)bytes.data() + bytes.size());

    ContextClient contextRequest(Coord{0, 0}, Player::Joker::NONE);
    contextRequest.FromJSONString(jsonString);

    scoped_lock lock(*mMutexPlayerCurrent);

    // not his turn
    if (player != mMatch.GetPlayerCurrent())
    {
        TRACE(format("\033[1;{}mPlayer\033[0m tried to make a move when it wasn't his turn...",
                     to_string((int)player.GetColor()))
                  .c_str());
        return CreateResponse(contextRequest, ContextServer::Error::TURN);
    }

    // has a joker active but could not activate on server side (it's already used)
    if (contextRequest.joker != Player::Joker::NONE && !player.SetActiveJoker(contextRequest.joker))
    {
        TRACE(format("\033[1;{}mPlayer\033[0m tried to use Joker::{} twice...", to_string((int)player.GetColor()),
                     Player::GetJokerName(contextRequest.joker))
                  .c_str());
        return CreateResponse(contextRequest, ContextServer::Error::JOKER);
    }

    // could not add the stone
    if (!mMatch.mBoard.AddStone(player, contextRequest.stone))
    {
        TRACE(vformat("\033[1;{}mPlayer\033[0m could not place stone({{ {}, {} }})...",
                      make_format_args(to_string((int)player.GetColor()),
                                       (int)contextRequest.stone.GetPosition().GetXY().first,
                                       (int)contextRequest.stone.GetPosition().GetXY().second))
                  .c_str());
        return CreateResponse(contextRequest, ContextServer::Error::STONE);
    }

    // cycle player and respond
    if (contextRequest.joker == Player::Joker::DOUBLE_MOVE)
    {
        player.UseActiveJoker();
    }
    else
    {
        mMatch.GetPlayerNext();
    }

    return CreateResponse(contextRequest, ContextServer::Error::NONE);
}

ContextServer MatchManager::CreateResponse(const ContextClient &contextRequest, const ContextServer::Error error)
{
    string message{format("\033[1;{}mPlayer\033[0m is next...", to_string((int)mMatch.GetPlayerCurrent().GetColor()))};
    switch (error)
    {
    case ContextServer::Error::TURN:
        message = "Wait your turn!"s;
        break;
    case ContextServer::Error::JOKER:
        message = format("Joker {} is already used!", Player::GetJokerName(contextRequest.joker));
        break;
    case ContextServer::Error::STONE:
        message = format("Could not add stone there!", Player::GetJokerName(contextRequest.joker));
        break;
    }

    return ContextServer(mMatch.mBoard, error, message);
}
} // namespace Server
