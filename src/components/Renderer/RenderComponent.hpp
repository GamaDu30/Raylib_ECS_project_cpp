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
    RenderComponent(Anchor anchor, raylib::Vector2 offset, raylib::Color color);
    ~RenderComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    virtual void OnRender();
};