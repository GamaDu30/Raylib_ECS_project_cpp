#pragma once

#include "raylib.h"
#include "raylib-cpp.hpp"

#define SCREEN_W 1280
#define SCREEN_H 720

class CircleCollider;
class RectCollider;

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

struct CollisionInfo
{
    virtual ~CollisionInfo() = default;
};

struct PolyColInfo : public CollisionInfo
{
    std::vector<raylib::Vector2> points;
    PolyColInfo(std::vector<raylib::Vector2> _points) : points(_points) {}
};

struct CircleColInfo : public CollisionInfo
{
    raylib::Vector2 pos;
    float radius;
    CircleColInfo(raylib::Vector2 _pos, float _radius) : pos(_pos), radius(_radius) {}
};

raylib::Vector2 GetAnchorOffset(Anchor anchor);

// Collisions Functions
bool ColCircleCircle(CircleColInfo *c1, CircleColInfo *c2);
bool ColPolyPoly(PolyColInfo *c1, PolyColInfo *c2);