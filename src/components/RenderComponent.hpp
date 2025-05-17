#pragma once

#include "definitions.hpp"
#include "components/Component.hpp"

class GameObject;

class RenderComponent : public Component
{
    static std::vector<RenderComponent *> m_renderers;

public:
    RenderComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();
};