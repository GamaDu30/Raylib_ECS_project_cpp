#pragma once

#include "global/definitions.hpp"
#include <functional>

enum KeyState
{
    DOWN,
    UP
};

class Inputs
{
private:
    static KeyboardKey inputKeys[349];

public:
    static std::unordered_map<KeyboardKey, std::vector<std::function<void()>>> inputMap;
    static void Init();

    template <typename T>
    static void RegisterInput(KeyboardKey key, KeyState keyState, T *instance, void (T::*method)());
    static void UnregisterInput(KeyboardKey key, KeyState keyState);

    static void Update();
};

template <typename T>
void Inputs::RegisterInput(KeyboardKey key, KeyState keyState, T *instance, void (T::*method)())
{
    inputMap[key][keyState] = std::bind(method, instance);
}