#include "definitions.hpp"

raylib::Vector2 GetAnchorOffset(Anchor anchor)
{
    switch (anchor)
    {
    case Anchor::TopLeft:
        return {0.0f, 0.0f};
    case Anchor::TopCenter:
        return {0.5f, 0.0f};
    case Anchor::TopRight:
        return {1.0f, 0.0f};
    case Anchor::CenterLeft:
        return {0.0f, 0.5f};
    case Anchor::Center:
        return {0.5f, 0.5f};
    case Anchor::CenterRight:
        return {1.0f, 0.5f};
    case Anchor::BottomLeft:
        return {0.0f, 1.0f};
    case Anchor::BottomCenter:
        return {0.5f, 1.0f};
    case Anchor::BottomRight:
        return {1.0f, 1.0f};
    }
    return {0.5f, 0.5f}; // fallback
}