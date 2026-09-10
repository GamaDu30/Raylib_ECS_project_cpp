#pragma once

#include "global/definitions.hpp"
#include "components/Component.hpp"

class GameObject;

class RenderComponentBase : public Component<RenderComponentBase>
{
protected:
    raylib::Color m_color = raylib::Color(255, 255, 255, 255);

    virtual void OnRender() = 0;

public:
    RenderComponentBase();
    ~RenderComponentBase();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    void Render();

    void SetColor(raylib::Color color);
};