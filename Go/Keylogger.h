#pragma once

class Keylogger
{
    class Accelerator
    {
      public:
        void Register(const vector<uint8_t> &keys, const function<void()> &callback);
        void Check();

      private:
        vector<tuple<vector<uint8_t>, function<void()>, bool>> mAccelerators{};
    };

  public:
    enum class Key
    {
        UP = VK_UP,
        RIGHT = VK_RIGHT,
        DOWN = VK_DOWN,
        LEFT = VK_LEFT,
        ENTER = VK_RETURN
    };

    Keylogger(function<void(const Key)> callback);

    void Check();

  private:
    Accelerator mAccelerator{};
    function<void(const Key)> mCallback{};
};