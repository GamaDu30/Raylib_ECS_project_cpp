#pragma once

#include "components/Component.hpp"
#include "components/TransformComponent.hpp"

class CanvasComponent;

class RectTransformComponent : public TransformComponent
{
    // Anchor values are normalized (0 to 1) and represent the percentage of the parent rectangle's size
    raylib::Vector2 m_anchorMin = raylib::Vector2(0, 0);
    raylib::Vector2 m_anchorMax = raylib::Vector2(1, 1);

    raylib::Vector2 m_size = raylib::Vector2(0, 0);
    raylib::Vector2 m_pivot = raylib::Vector2(0.5f, 0.5f);

public:
    RectTransformComponent();
    ~RectTransformComponent();

    virtual void Init(GameObject *owner) override;
    virtual void Update() override;
    virtual void Destroy() override;

    raylib::Vector2 &GetAnchorMin();
    raylib::Vector2 &GetAnchorMax();

    void SetSize(raylib::Vector2 size = raylib::Vector2(100, 100));
    void SetPivot(raylib::Vector2 pivot = raylib::Vector2(0.5f, 0.5f));

    raylib::Rectangle GetWorldRectangle();

    void DebugRender();
};