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

void ContextClient::to_json(nlohmann::json &nlohmann_json_j, const ContextClient &nlohmann_json_t)
{
    nlohmann::to_json(nlohmann_json_j, static_cast<const IContext &>(nlohmann_json_t));
    nlohmann_json_j["stone"] = nlohmann_json_t.stone;
    nlohmann_json_j["joker"] = nlohmann_json_t.joker;
}

void ContextClient::from_json(const nlohmann::json &nlohmann_json_j, ContextClient &nlohmann_json_t)
{
    nlohmann::from_json(nlohmann_json_j, static_cast<IContext &>(nlohmann_json_t));
    nlohmann_json_j.at("stone").get_to(nlohmann_json_t.stone);
    nlohmann_json_j.at("joker").get_to(nlohmann_json_t.joker);
}

ContextClient::ContextClient(const Stone &stone, const Player::Joker joker)
    : IContext(IContext::Type::CLIENT), stone(stone), joker(joker)
{
}

void ContextServerInit::to_json(nlohmann::json &nlohmann_json_j, const ContextServerInit &nlohmann_json_t)
{
    nlohmann::to_json(nlohmann_json_j, static_cast<const IContext &>(nlohmann_json_t));
    nlohmann_json_j["rules"] = nlohmann_json_t.rules;
    nlohmann_json_j["color"] = nlohmann_json_t.color;
}

void ContextServerInit::from_json(const nlohmann::json &nlohmann_json_j, ContextServerInit &nlohmann_json_t)
{
    nlohmann::from_json(nlohmann_json_j, static_cast<IContext &>(nlohmann_json_t));
    nlohmann_json_j.at("rules").get_to(nlohmann_json_t.rules);
    nlohmann_json_j.at("color").get_to(nlohmann_json_t.color);
}

ContextServerInit::ContextServerInit(const Rules &rules, const Player::Color color)
    : IContext(IContext::Type::SERVER_INIT), rules(rules), color(color)
{
}

void ContextServerUninit::to_json(nlohmann::json &nlohmann_json_j, const ContextServerUninit &nlohmann_json_t)
{
    nlohmann::to_json(nlohmann_json_j, static_cast<const IContext &>(nlohmann_json_t));
    nlohmann_json_j["winner"] = nlohmann_json_t.winner;
}

void ContextServerUninit::from_json(const nlohmann::json &nlohmann_json_j, ContextServerUninit &nlohmann_json_t)
{
    nlohmann::from_json(nlohmann_json_j, static_cast<IContext &>(nlohmann_json_t));
    nlohmann_json_j.at("winner").get_to(nlohmann_json_t.winner);
}

ContextServerUninit::ContextServerUninit(const Player::Color winner)
    : IContext(IContext::Type::SERVER_UNINIT), winner(winner)
{
}

void ContextServer::to_json(nlohmann::json &nlohmann_json_j, const ContextServer &nlohmann_json_t)
{
    nlohmann::to_json(nlohmann_json_j, static_cast<const IContext &>(nlohmann_json_t));
    nlohmann_json_j["board"] = nlohmann_json_t.board;
    nlohmann_json_j["message"] = nlohmann_json_t.message;
}

void ContextServer::from_json(const nlohmann::json &nlohmann_json_j, ContextServer &nlohmann_json_t)
{
    nlohmann::from_json(nlohmann_json_j, static_cast<IContext &>(nlohmann_json_t));
    nlohmann_json_j.at("board").get_to(nlohmann_json_t.board);
    nlohmann_json_j.at("message").get_to(nlohmann_json_t.message);
}

ContextServer::ContextServer(const Board &board, const Error error, const string &message)
    : IContext(IContext::Type::SERVER), board(board), error(error), message(message)
{
}
} // namespace Game
