#pragma once

#include "Client.h"
#include "Go/Game/Board.h"
#include "Gome/Networking/IOContext.h"
#include "Keylogger.h"

using namespace Game;

namespace Client
{
/**
 * @brief The Go game implementation as client
 */
class GameI
{
  public:
    /**
     * @brief Constructor
     * @param context the context
     */
    GameI(Networking::IOContext &context);

    /**
     * @brief Starts the game
     */
    void Run();

  private:
    mutex mMutexConsole;
    atomic<bool> mReady{};
    atomic<bool> mFinished{};

    COORD mCurrentPositionInBoard{};
    Keylogger mKeylogger;

    Board mBoard{Coord{0, 0}};
    deque<string> mMessages{};

    Client mClient;
    Player mPlayer{Player::Color::NONE};

    /**
     * @brief Draws the CLI
     */
    void Draw();

    /**
     * @brief Draws the game board
     */
    void DrawBoard() const;

    /**
     * @brief Draws the jokers state and your color
     */
    void DrawJokersStateAndPlayerColor() const;

    /**
     * @brief Draws the last queue informative messages from the server
     */
    void DrawMessages() const;

    /**
     * @brief Draws a line divider for the game board
     * @param row the row index from the board
     */
    void DrawLineDivider(const uint8_t row) const;

    /**
     * @brief Draws the top line from the game board
     */
    void DrawLineBorderTop() const;

    /**
     * @brief Draws the bottom line from the game board
     */
    void DrawLineBorderBottom() const;

    /**
     * @brief Sets the console caret position
     * @param point the position
     */
    static void GetCaretPos(POINT *point);

    /**
     * @brief Gets the console caret position
     * @param x the x axis
     * @param y the y axis
     */
    static void SetCaretPos(int x, int y);

    /**
     * @brief Resets the console caret and optionally clears the console before that
     * @param clearConsoleBefore clear the console before resetting the caret
     */
    void ResetCaret(const bool clearConsoleBefore = true) const;

    /**
     * @brief Converts a board position to the console position
     * @param position the board position
     * @return the console position
     */
    COORD BoardToConsolePosition(const COORD &position) const;

    /**
     * @brief Event handler that sets the joker of the player
     * @param key the joker
     */
    void SetJoker(const Keylogger::Key key);

    /**
     * @brief Event handler that gets the current position in the console and makes a request to add the stone
     */
    void AddStone();

    /**
     * @brief Event handler for any key press
     * @param key the key
     */
    void OnKeyPress(const Keylogger::Key key);

    /**
     * @brief Event handler for a move key
     * @param key the move key
     */
    void Move(const Keylogger::Key key);

    /**
     * @brief Initializes the console interface
     */
    void InitializeCLI() const;

    /**
     * @brief Event handler for initializing the game
     * @param contextInit the initializing context
     */
    void OnInitialize(const ContextServerInit &contextInit);

    /**
     * @brief Event handler for on going game updates
     * @param context the current context
     */
    void OnUpdate(const ContextServer &context);

    /**
     * @brief Event handler for uninitializing the game
     * @param contextInit the uninitializing context
     */
    void OnUninitialize(const ContextServerUninit &contextUninit);
};
} // namespace Client
