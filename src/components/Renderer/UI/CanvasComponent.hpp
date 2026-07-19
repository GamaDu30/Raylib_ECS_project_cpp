#pragma once

#include "components/Component.hpp"

class GameObject;
class RectTransformComponent;

class CanvasComponent : public Component
{
    ViewMode m_viewMode = ViewMode::ScreenSpace;

public:
    CanvasComponent();
    ~CanvasComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    void Render();

    ViewMode GetViewMode();
    raylib::Rectangle GetBorder();
};