#pragma once

#include "components/Component.hpp"

class RectTransformComponent;
class CanvasComponent;

class UIRenderComponent : public Component<UIRenderComponent>
{
protected:
    RectTransformComponent *m_rectTransformComp = nullptr;

    raylib::Color m_color = raylib::Color(255, 255, 255, 255);

public:
    UIRenderComponent();
    ~UIRenderComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    virtual void Render();

    virtual void SetColor(raylib::Color color);

    raylib::Rectangle GetCollision();
};