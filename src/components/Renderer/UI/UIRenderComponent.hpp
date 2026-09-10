#pragma once

#include "global/definitions.hpp"
#include "components/Renderer/RenderComponentBase.hpp"

class RectTransformComponent;
class CanvasComponent;

class UIRenderComponent : public RenderComponentBase
{
protected:
    RectTransformComponent *m_rectTransformComp = nullptr;

public:
    UIRenderComponent();
    ~UIRenderComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    virtual void OnRender();

    raylib::Rectangle GetCollision();
};