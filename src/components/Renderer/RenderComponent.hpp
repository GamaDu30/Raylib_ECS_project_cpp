#pragma once

#include "global/definitions.hpp"
#include "components/Component.hpp"

class GameObject;

class RenderComponent : public Component
{
    static std::vector<RenderComponent *> m_renderers;

protected:
    Anchor m_anchor;
    raylib::Vector2 m_offset;
    raylib::Color m_color;

public:
    RenderComponent(Anchor anchor, raylib::Vector2 offset, raylib::Color color);

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();

    void SetColor(raylib::Color color);
};