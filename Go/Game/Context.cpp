#include "Go/pch.h"

#include "Context.h"

namespace Game
{
IContext::IContext(const Type type) : mType(type)
{
}

string IContext::ToJSONString() const
{
    json contextJSON;

    switch (mType)
    {
    case Type::CLIENT: {
        ContextClient &context = *(ContextClient *)this;
        context.to_json(contextJSON, context);
    }
    break;
    case Type::SERVER_INIT: {
        ContextServerInit &context = *(ContextServerInit *)this;
        context.to_json(contextJSON, context);
    }
    break;
    case Type::SERVER: {
        ContextServer &context = *(ContextServer *)this;
        context.to_json(contextJSON, context);
    }
    break;
    case Type::SERVER_UNINIT: {
        ContextServerUninit &context = *(ContextServerUninit *)this;
        context.to_json(contextJSON, context);
    }
    break;
    }

    return contextJSON.dump();
}

void IContext::FromJSONString(const string &jsonString)
{
    auto &&json = json::parse(jsonString);

    switch (mType)
    {
    case Type::CLIENT: {
        ContextClient &context = *(ContextClient *)this;
        context.from_json(json, context);
    }
    break;
    case Type::SERVER_INIT: {
        ContextServerInit &context = *(ContextServerInit *)this;
        context.from_json(json, context);
    }
    break;
    case Type::SERVER: {
        ContextServer &context = *(ContextServer *)this;
        context.from_json(json, context);
    }
    break;
    case Type::SERVER_UNINIT: {
        ContextServerUninit &context = *(ContextServerUninit *)this;
        context.from_json(json, context);
    }
    break;
    }
}

IContext::Type IContext::GetType() const
{
    return mType;
}

ContextClient::ContextClient(const Stone &stone, const Player::Joker joker)
    : IContext(IContext::Type::CLIENT), stone(stone), joker(joker)
{
}

ContextServerInit::ContextServerInit(const Rules &rules, const Player::Color color)
    : IContext(IContext::Type::SERVER_INIT), rules(rules), color(color)
{
}

ContextServerUninit::ContextServerUninit(const Player::Color winner)
    : IContext(IContext::Type::SERVER_UNINIT), winner(winner)
{
}

ContextServer::ContextServer(const Board &board, const string &message)
    : IContext(IContext::Type::SERVER), board(board), message(message)
{
}
} // namespace Game
