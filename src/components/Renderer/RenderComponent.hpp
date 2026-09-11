#pragma once

#include "global/definitions.hpp"
#include "components/Renderer/RenderComponentBase.hpp"

class GameObject;

class RenderComponent : public RenderComponentBase
{
protected:
    Anchor m_anchor;
    raylib::Vector2 m_offset;

public:
    RenderComponent(Anchor anchor = Anchor::Center, raylib::Vector2 offset = raylib::Vector2(), raylib::Color color = WHITE);
    ~RenderComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    virtual void OnRender();
};