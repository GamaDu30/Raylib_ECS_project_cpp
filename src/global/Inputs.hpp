#pragma once

#include "global/definitions.hpp"
#include <functional>

template <typename... Args>
class Event;

enum KeyState
{
    PRESSED,
    RELEASED
};

class Inputs
{
private:
    // struct InputCallback
    // {
    //     void *owner;
    //     std::function<void()> method;
    // };

    static KeyboardKey inputKeys[349];

public:
    static std::unordered_map<KeyboardKey, std::array<Event<>, 2>> inputMap;

    static void Init();

    static int RegisterInput(KeyboardKey key, KeyState keyState, std::function<void()> method);
    static void UnregisterInput(KeyboardKey key = KEY_NULL, KeyState keyState = PRESSED);
    static void UnregisterInput(size_t id);

    static void Update();
};