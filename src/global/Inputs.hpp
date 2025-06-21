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
    static KeyboardKey inputKeys[349];

public:
    static std::unordered_map<KeyboardKey, std::array<std::vector<std::function<void()>>, 2>> inputMap;

    static void Init();

    static void RegisterInput(KeyboardKey key, KeyState keyState, std::function<void()> method);
    static void UnregisterInput(KeyboardKey key, KeyState keyState);

    static void Update();
};