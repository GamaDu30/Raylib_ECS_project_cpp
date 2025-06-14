#pragma once

#include "global/definitions.hpp"
#include "components/Renderer/RenderComponent.hpp"

class CircleRenderer : public RenderComponent
{
    float m_radius;
    bool m_isFilled;

public:
    CircleRenderer(float radius, raylib::Vector2 offset = raylib::Vector2(), raylib::Color color = WHITE, Anchor anchor = Anchor::Center, bool isFilled = true)
        : RenderComponent(anchor, offset, color), m_radius(radius), m_isFilled(isFilled) {}

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();

    raylib::Vector2 &GetPos();
};