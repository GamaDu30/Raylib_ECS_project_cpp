#pragma once

#include "global/definitions.hpp"
#include <functional>
#include <cstdint>

enum KeyState
{
    PRESSED,
    RELEASED
};

class Inputs
{
private:
    struct InputCallback
    {
        std::uint64_t id;
        std::function<void()> method;
    };

    static KeyboardKey inputKeys[349];
    static std::uint64_t nextCallbackId;

public:
    static std::unordered_map<KeyboardKey, std::array<std::vector<InputCallback>, 2>> inputMap;

    static void Init();

    static std::uint64_t RegisterInput(KeyboardKey key, KeyState keyState, std::function<void()> method);
    static void UnregisterInput(KeyboardKey key, KeyState keyState);
    static void UnregisterInput(KeyboardKey key, KeyState keyState, std::uint64_t callbackId);

    static void Update();
};