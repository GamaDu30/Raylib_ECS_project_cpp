#include "components/RectTransformComponent.hpp"
#include "components/Component.hpp"
#include "components/Renderer/UI/CanvasComponent.hpp"
#include "global/gameObject.hpp"

RectTransformComponent::RectTransformComponent()
{
}

RectTransformComponent::~RectTransformComponent()
{
}

void RectTransformComponent::Init(GameObject *owner)
{
    TransformComponent::Init(owner);
}

void RectTransformComponent::Update()
{
    TransformComponent::Update();

    if (m_anchorMin.GetX() > m_anchorMax.GetX())
    {
        float tempX = m_anchorMin.GetX();
        m_anchorMin.SetX(m_anchorMax.GetX());
        m_anchorMax.SetX(tempX);
    }

    if (m_anchorMin.GetY() > m_anchorMax.GetY())
    {
        float tempY = m_anchorMin.GetY();
        m_anchorMin.SetY(m_anchorMax.GetY());
        m_anchorMax.SetY(tempY);
    }
}

void RectTransformComponent::Destroy()
{
    TransformComponent::Destroy();
}

raylib::Vector2 &RectTransformComponent::GetAnchorMin()
{
    return m_anchorMin;
}

raylib::Vector2 &RectTransformComponent::GetAnchorMax()
{
    return m_anchorMax;
}

raylib::Rectangle RectTransformComponent::GetWorldRectangle()
{
    raylib::Rectangle border;
    CanvasComponent *canvas = m_owner->GetComponent<CanvasComponent>();

    if (canvas)
    {
        border = canvas->GetBorder();
    }
    else
    {
        border = dynamic_cast<RectTransformComponent *>(GetParent())->GetWorldRectangle();
    }

    raylib::Vector2 posMin;
    posMin.x = border.GetX() + border.GetWidth() * m_anchorMin.x;
    posMin.y = border.GetY() + border.GetHeight() * m_anchorMin.y;

    raylib::Vector2 posMax;
    posMax.x = border.GetX() + border.GetWidth() * m_anchorMax.x;
    posMax.y = border.GetY() + border.GetHeight() * m_anchorMax.y;

    return raylib::Rectangle(posMin, raylib::Vector2(posMax.x - posMin.x, posMax.y - posMin.y));
}

void RectTransformComponent::DebugRender()
{
    raylib::Rectangle worldRect = GetWorldRectangle();
    worldRect.DrawLines(WHITE, 1);
    DrawText(m_owner->GetName().c_str(), worldRect.GetX() + 8, worldRect.GetY() + 8, 15, WHITE);

    for (TransformComponent *child : GetChildren())
    {
        dynamic_cast<RectTransformComponent *>(child)->DebugRender();
    }
}