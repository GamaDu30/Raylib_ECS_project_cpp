#include "components/RectTransformComponent.hpp"
#include "components/Component.hpp"
#include "components/Renderer/UI/CanvasComponent.hpp"
#include "global/gameObject.hpp"
#include "RectTransformComponent.hpp"

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

void RectTransformComponent::SetFixed(bool isFixedX, bool isFixedY, raylib::Vector2 sizePixels, raylib::Vector2 anchorPoint)
{
    m_isFixedX = isFixedX;
    m_isFixedY = isFixedY;
    m_size = sizePixels;
    m_anchorPoint = anchorPoint;
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

    raylib::Rectangle finalRect = raylib::Rectangle();

    if (m_isFixedX)
    {
        finalRect.SetX(border.GetX() + border.GetWidth() * m_anchorPoint.x - m_size.x * 0.5f);
        finalRect.SetWidth(m_size.x);
    }
    else
    {
        finalRect.SetX(border.GetX() + border.GetWidth() * m_anchorMin.x);
        finalRect.SetWidth(border.GetWidth() * (m_anchorMax.x - m_anchorMin.x));
    }

    // Y axis
    if (m_isFixedY)
    {
        finalRect.SetY(border.GetY() + border.GetHeight() * m_anchorPoint.y - m_size.y * 0.5f);
        finalRect.SetHeight(m_size.y);
    }
    else
    {
        finalRect.SetY(border.GetY() + border.GetHeight() * m_anchorMin.y);
        finalRect.SetHeight(border.GetHeight() * (m_anchorMax.y - m_anchorMin.y));
    }

    return finalRect;
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