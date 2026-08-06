#pragma once

#include "global/definitions.hpp"
#include <functional>

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
        void *owner;
        std::function<void()> method;
    };

    static KeyboardKey inputKeys[349];

public:
    static std::unordered_map<KeyboardKey, std::array<std::vector<InputCallback>, 2>> inputMap;

    static void Init();

    static void RegisterInput(KeyboardKey key, KeyState keyState, void *owner, std::function<void()> method);
    static void UnregisterInput(KeyboardKey key, KeyState keyState);
    static void UnregisterInput(KeyboardKey key, KeyState keyState, void *owner);

    static void Update();
};