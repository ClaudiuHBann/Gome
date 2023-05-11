#pragma once

#include "Client.h"
#include "Go/Game/Board.h"
#include "Gome/Networking/IOContext.h"
#include "Keylogger.h"

using namespace Game;

namespace Client
{
class GameI
{
  public:
    GameI(Networking::IOContext &context);

    void Run();

  private:
    mutex mMutexConsole;
    atomic<bool> mReady{};
    atomic<bool> mFinished{};

    COORD mCurrentPositionInBoard{};
    HANDLE mHandleConsoleOutput{};
    Keylogger mKeylogger;

    Board mBoard{Coord{0, 0}};
    deque<string> mMessages{};

    Client mClient;
    Player mPlayer{Player::Color::NONE};

    void Draw();
    void DrawBoard() const;
    void DrawJokersState() const;
    void DrawMessages() const;
    void DrawLineDivider(const uint8_t row) const;
    void DrawLineBorderTop() const;
    void DrawLineBorderBottom() const;

    void ResetCursor(const bool clearConsoleBefore = true) const;
    COORD BoardToConsolePosition(const COORD &position) const;

    void SetJoker(const Keylogger::Key key);
    void AddStone();
    void OnKeyPress(const Keylogger::Key key);
    void Move(const Keylogger::Key key);

    void InitializeCLI() const;
    void OnInitialize(const ContextServerInit &contextInit);
    void OnUpdate(const ContextServer &context);
    void OnUninitialize(const ContextServerUninit &contextUninit);
};
} // namespace Client
