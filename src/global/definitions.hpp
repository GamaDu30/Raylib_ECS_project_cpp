#pragma once

#include "raylib.h"
#include "raylib-cpp.hpp"

#define SCREEN_W 1280
#define SCREEN_H 720

enum class Anchor
{
    TopLeft,
    TopCenter,
    TopRight,
    CenterLeft,
    Center,
    CenterRight,
    BottomLeft,
    BottomCenter,
    BottomRight
};

raylib::Vector2 GetAnchorOffset(Anchor anchor);