#include "Go/pch.h"

#include "Game.h"

constexpr uint8_t CORNER_LEFT_UP = 218;
constexpr uint8_t CORNER_RIGHT_UP = 191;
constexpr uint8_t CORNER_LEFT_DOWN = 192;
constexpr uint8_t CORNER_RIGHT_DOWN = 217;

constexpr uint8_t PIECE_MIDDLE = 197;
constexpr uint8_t PIECE_VERTICAL = 179;
constexpr uint8_t PIECE_VERTICAL_LEFT = 195;
constexpr uint8_t PIECE_VERTICAL_RIGHT = 180;
constexpr uint8_t PIECE_HORIZONTAL = 196;
constexpr uint8_t PIECE_HORIZONTAL_DOWN = 193;
constexpr uint8_t PIECE_HORIZONTAL_UP = 194;

namespace Client
{
GameI::GameI(Networking::IOContext &context)
    : mKeylogger(bind(&GameI::OnKeyPress, this, std::placeholders::_1)),
      mClient(context, bind(&GameI::OnInitialize, this, std::placeholders::_1),
              bind(&GameI::OnUpdate, this, std::placeholders::_1),
              bind(&GameI::OnUninitialize, this, std::placeholders::_1))
{
    InitializeCLI();

    mClient.Connect(SERVER_IP, SERVER_PORT);
}

void GameI::OnKeyPress(const Keylogger::Key key)
{
    if (key == Keylogger::Key::ENTER)
    {
        AddStone();
    }
    else if (key == Keylogger::Key::F1 || key == Keylogger::Key::F2 || key == Keylogger::Key::F3)
    {
        SetJoker(key);
    }
    else
    {
        Move(key);
    }

    Draw();
}

void GameI::SetJoker(const Keylogger::Key key)
{
    switch (key)
    {
    case Keylogger::Key::F1: {
        if (mPlayer.GetActiveJoker() == Player::Joker::DOUBLE_MOVE)
        {
            mPlayer.SetActiveJoker(Player::Joker::NONE);
        }
        else
        {
            mPlayer.SetActiveJoker(Player::Joker::DOUBLE_MOVE);
        }
    }
    break;
    case Keylogger::Key::F2: {
        if (mPlayer.GetActiveJoker() == Player::Joker::REPLACE)
        {
            mPlayer.SetActiveJoker(Player::Joker::NONE);
        }
        else
        {
            mPlayer.SetActiveJoker(Player::Joker::REPLACE);
        }
    }
    break;
    case Keylogger::Key::F3: {
        if (mPlayer.GetActiveJoker() == Player::Joker::FREEDOM)
        {
            mPlayer.SetActiveJoker(Player::Joker::NONE);
        }
        else
        {
            mPlayer.SetActiveJoker(Player::Joker::FREEDOM);
        }
    }
    break;
    }
}

void GameI::AddStone()
{
    TRACE_NO_STDOUT("Adding stone...");

    ContextClient context(Coord{(uint8_t)mCurrentPositionInBoard.X, (uint8_t)mCurrentPositionInBoard.Y},
                          mPlayer.GetActiveJoker());
    mClient.Send(context);
}

void GameI::InitializeCLI() const
{
    TRACE("Initializing CLI...");

    // set console code page to print extended ASCII chars
    SetConsoleOutputCP(437);

    // enable virtual terminal processing for console virtual terminal sequences
    // which we are going to use for changing the caret
    DWORD dwMode{};
    GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), dwMode);

    cout << "\x1b[1\x20q";
}

void GameI::OnInitialize(const ContextServerInit &contextInit)
{
    TRACE("Initializing match...");

    mPlayer = Player(contextInit.color);
    mBoard = Board(contextInit.rules.GetSize());

    mReady = true;
}

void GameI::OnUninitialize(const ContextServerUninit &contextUninit)
{
    TRACE_NO_STDOUT(contextUninit.message);

    mMessages.push_back(contextUninit.message);
    if (mMessages.size() > 5)
    {
        mMessages.pop_front();
    }

    Draw();

    mClient.Disconnect();
    mFinished = true;
}

void GameI::OnUpdate(const ContextServer &context)
{
    if (!mReady && context.error == ContextServer::Error::WAIT)
    {
        TRACE(context.message);
        return;
    }

    TRACE_NO_STDOUT("Updating board and messages...");

    mBoard = context.board;
    mPlayer = Player(mPlayer.GetColor(), context.jokers);

    mMessages.push_front(context.message);
    if (mMessages.size() > 5)
    {
        mMessages.pop_back();
    }

    Draw();
}

void GameI::Run()
{
    while (!mReady)
    {
    }

    ResetCaret();
    Draw();

    while (!mFinished)
    {
        mKeylogger.Check();
    }
}

void GameI::DrawBoard() const
{
    ResetCaret(false);

    DrawLineBorderTop();
    for (uint8_t row = 1; row < mBoard.GetSize().GetXY().first - 1; row++)
    {
        DrawLineDivider(row);
    }
    DrawLineBorderBottom();
}

/* static */ void GameI::GetCaretPos(POINT *point)
{
    static auto handleConsoleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi{};
    GetConsoleScreenBufferInfo(handleConsoleStdOut, &csbi);

    point->x = csbi.dwCursorPosition.X;
    point->y = csbi.dwCursorPosition.Y;
}

/* static */ void GameI::SetCaretPos(int x, int y)
{
    static auto handleConsoleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(handleConsoleStdOut, {(SHORT)x, (SHORT)y});
}

void GameI::DrawJokersStateAndPlayerColor() const
{

    SetCaretPos(mBoard.GetSize().GetXY().second * 2, 1);
    cout << format("Your color is \033[1;{}m{}\033[0m", to_string((int)mPlayer.GetColor()),
                   Player::GetColorName(mPlayer.GetColor()));

    // READY (GREEN) -> ACTIVE (YELLOW) -> USED (RED)
    const auto &jokers = mPlayer.GetJokers();
    for (size_t i = 0; i < jokers.size(); i++)
    {
        string color("32"s);
        string text("READY "s);
        if (!jokers[i].second)
        {
            color = mPlayer.GetActiveJoker() == jokers[i].first ? "33"s : "31"s;
            text = mPlayer.GetActiveJoker() == jokers[i].first ? "ACTIVE"s : "USED  "s;
        }

        SetCaretPos(mBoard.GetSize().GetXY().second * 2, i + 2);
        cout << format("(F{}) Joker {}: \033[1;{}m{}\033[0m", i + 1, Player::GetJokerName(jokers[i].first), color,
                       text);
    }
}

void GameI::DrawMessages() const
{
    SetCaretPos(0, mBoard.GetSize().GetXY().first + 1);
    for (const auto &message : mMessages)
    {
        cout << "\33[2K\r"; // clear line before writing the message
        cout << format(" {}", message) << endl;
    }
}

void GameI::Draw()
{
    scoped_lock lock(mMutexConsole);

    POINT caretPosStart{};
    GetCaretPos(&caretPosStart);

    DrawBoard();
    DrawJokersStateAndPlayerColor();
    DrawMessages();

    SetCaretPos(caretPosStart.x, caretPosStart.y);
}

void GameI::DrawLineDivider(const uint8_t row) const
{
    cout << mBoard.GetStoneColorOrAsString({row, 0}, PIECE_VERTICAL_LEFT);
    for (uint8_t column = 1; column < mBoard.GetSize().GetXY().second - 1; column++)
    {
        cout << PIECE_HORIZONTAL << mBoard.GetStoneColorOrAsString({row, column}, PIECE_MIDDLE);
    }
    cout << PIECE_HORIZONTAL
         << mBoard.GetStoneColorOrAsString({row, uint8_t(mBoard.GetSize().GetXY().second - 1)}, PIECE_VERTICAL_RIGHT)
         << endl;
}

void GameI::DrawLineBorderTop() const
{
    cout << mBoard.GetStoneColorOrAsString({0, 0}, CORNER_LEFT_UP);
    for (uint8_t column = 1; column < mBoard.GetSize().GetXY().second - 1; column++)
    {
        cout << PIECE_HORIZONTAL << mBoard.GetStoneColorOrAsString({0, column}, PIECE_HORIZONTAL_UP);
    }
    cout << PIECE_HORIZONTAL
         << mBoard.GetStoneColorOrAsString({0, uint8_t(mBoard.GetSize().GetXY().second - 1)}, CORNER_RIGHT_UP) << endl;
}

void GameI::DrawLineBorderBottom() const
{
    cout << mBoard.GetStoneColorOrAsString({uint8_t(mBoard.GetSize().GetXY().first - 1), 0}, CORNER_LEFT_DOWN);
    for (uint8_t column = 1; column < mBoard.GetSize().GetXY().second - 1; column++)
    {
        cout << PIECE_HORIZONTAL
             << mBoard.GetStoneColorOrAsString({uint8_t(mBoard.GetSize().GetXY().first - 1), column},
                                               PIECE_HORIZONTAL_DOWN);
    }
    cout << PIECE_HORIZONTAL
         << mBoard.GetStoneColorOrAsString(
                {uint8_t(mBoard.GetSize().GetXY().first - 1), uint8_t(mBoard.GetSize().GetXY().second - 1)},
                CORNER_RIGHT_DOWN)
         << endl;
}

void GameI::ResetCaret(const bool clearConsoleBefore /* = true */) const
{
    if (clearConsoleBefore)
    {
        static auto console = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_SCREEN_BUFFER_INFO csbi{};
        GetConsoleScreenBufferInfo(console, &csbi);

        DWORD writtenCharsCount{};
        FillConsoleOutputCharacter(console, ' ', csbi.dwSize.X * csbi.dwSize.Y, {}, &writtenCharsCount);

        FillConsoleOutputAttribute(console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
                                   csbi.dwSize.X * csbi.dwSize.Y, {}, &writtenCharsCount);
        SetConsoleCursorPosition(console, {});
    }

    SetCaretPos(0, 0);
}

COORD GameI::BoardToConsolePosition(const COORD &position) const
{
    return COORD(position.Y * 2, position.X);
}

void GameI::Move(const Keylogger::Key key)
{
    auto newPositionInBoard = mCurrentPositionInBoard;
    switch (key)
    {
    case Keylogger::Key::UP:
        newPositionInBoard.X--;
        break;
    case Keylogger::Key::RIGHT:
        newPositionInBoard.Y++;
        break;
    case Keylogger::Key::DOWN:
        newPositionInBoard.X++;
        break;
    case Keylogger::Key::LEFT:
        newPositionInBoard.Y--;
        break;
    }

    if (mBoard.IsPositionValid({(uint8_t)newPositionInBoard.X, (uint8_t)newPositionInBoard.Y}))
    {
        mCurrentPositionInBoard = move(newPositionInBoard);
        auto &&caretPosNew = BoardToConsolePosition(mCurrentPositionInBoard);
        SetCaretPos(caretPosNew.X, caretPosNew.Y);
    }
}
} // namespace Client
