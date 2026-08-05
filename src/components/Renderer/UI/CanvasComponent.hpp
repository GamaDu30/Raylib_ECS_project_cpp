#pragma once

#include "components/Component.hpp"

class GameObject;

class CanvasComponent : public Component<CanvasComponent>
{
    ViewMode m_viewMode = ViewMode::ScreenSpace;

public:
    CanvasComponent();
    ~CanvasComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    void Render();

    ViewMode GetViewMode();
    raylib::Rectangle GetBorder();
};