#pragma once

#include "components/Component.hpp"

class RectTransformComponent;
class CanvasComponent;

class UIRenderComponent : public Component
{
protected:
    RectTransformComponent *m_rectTransformComp = nullptr;

public:
    UIRenderComponent();
    ~UIRenderComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();
};