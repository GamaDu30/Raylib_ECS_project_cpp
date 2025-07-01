#include "components/Renderer/RectRenderer.hpp"

RectRenderer::RectRenderer(raylib::Vector2 size, raylib::Vector2 offset, Anchor anchor, Color color, bool filled) : RenderComponent(anchor, offset, color)
{
    m_rect = raylib::Rectangle(m_offset, size);
    m_filled = filled;
}

void RectRenderer::Init(GameObject *owner)
{
    RenderComponent::Init(owner);
}

void RectRenderer::Update()
{
    RenderComponent::Update();
}

void RectRenderer::Destroy()
{
    RenderComponent::Destroy();
}

void RectRenderer::Render()
{
    RenderComponent::Render();

    raylib::Vector2 offset = GetAnchorOffset(m_anchor);

    rlTranslatef(m_offset.x - m_rect.GetSize().x * offset.x, m_offset.y - m_rect.GetSize().y * offset.y, 0);

    if (m_filled)
    {
        m_rect.Draw(m_color);
    }
    else
    {
        m_rect.DrawLines(m_color);
    }

    rlPopMatrix();
}