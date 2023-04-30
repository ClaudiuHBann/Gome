#include "Go/pch.h"

#include "Keylogger.h"

void Keylogger::Accelerator::Register(const vector<uint8_t> &keys, const function<void()> &callback)
{
    mAccelerators.push_back({keys, callback, false});
}

void Keylogger::Accelerator::Check()
{
    for (auto &[keys, callback, state] : mAccelerators)
    {
        bool fire = true;
        for (const auto &key : keys)
        {
            if (GetKeyState(key) >= 0)
            {
                fire = false;
                break;
            }
        }

        if (!state && fire)
        {
            callback();
        }
        state = fire;
    }
}

Keylogger::Keylogger(function<void(const Key)> callback) : mCallback(callback)
{
    mAccelerator.Register({(int)Key::UP}, [&]() { mCallback(Key::UP); });
    mAccelerator.Register({(int)Key::RIGHT}, [&]() { mCallback(Key::RIGHT); });
    mAccelerator.Register({(int)Key::DOWN}, [&]() { mCallback(Key::DOWN); });
    mAccelerator.Register({(int)Key::LEFT}, [&]() { mCallback(Key::LEFT); });
    mAccelerator.Register({(int)Key::ENTER}, [&]() { mCallback(Key::ENTER); });
}

void Keylogger::Check()
{
    mAccelerator.Check();
}
