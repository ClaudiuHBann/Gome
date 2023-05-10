#pragma once

namespace Client
{
/**
 * @brief Checks for game specific combinations of keys
 */
class Keylogger
{
    /**
     * @brief Checks for combinations of key presses
     */
    class Accelerator
    {
      public:
        /**
         * @brief Registers a combinations of keys and the callback for when they are pressed
         * @param keys the combination of keys
         * @param callback the callback to be invoked
         */
        void Register(const vector<uint8_t> &keys, const function<void()> &callback);

        /**
         * @brief Checks all the accelerators
         */
        void Check();

      private:
        vector<tuple<vector<uint8_t>, function<void()>, bool>> mAccelerators{};
    };

  public:
    /**
     * @brief The keys that we handle for the game
     */
    enum class Key
    {
        UP = VK_UP,
        RIGHT = VK_RIGHT,
        DOWN = VK_DOWN,
        LEFT = VK_LEFT,
        ENTER = VK_RETURN,
        F1 = VK_F1,
        F2 = VK_F2,
        F3 = VK_F3
    };

    /**
     * @brief Constructor
     * @param callback the callback that is invoked when a game key combination is pressed
     */
    Keylogger(function<void(const Key)> callback);

    /**
     * @brief Checks all the accelerators
     */
    void Check();

  private:
    Accelerator mAccelerator{};
    function<void(const Key)> mCallback{};
};
} // namespace Client
