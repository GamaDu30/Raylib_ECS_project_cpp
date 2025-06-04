#pragma once

#include "definitions.hpp"
#include "components/Component.hpp"

class GameObject;

class RenderComponent : public Component
{
    static std::vector<RenderComponent *> m_renderers;

protected:
    Anchor m_anchor;

public:
    RenderComponent(Anchor anchor);

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();
};