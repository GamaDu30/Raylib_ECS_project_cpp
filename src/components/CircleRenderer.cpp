#include "components/CircleRenderer.hpp"

void CircleRenderer::Init(GameObject *owner)
{
    RenderComponent::Init(owner);
}

void CircleRenderer::Update()
{
    RenderComponent::Update();
}

void CircleRenderer::Destroy()
{
    RenderComponent::Update();
}

void CircleRenderer::Render()
{
    RenderComponent::Render();

    raylib::Vector2 offset = GetAnchorOffset(m_anchor);

    offset *= -2;
    offset += raylib::Vector2(1, 1);

    rlTranslatef(m_pos.x + m_radius * offset.x, m_pos.y + m_radius * offset.y, 0);

    if (m_isFilled)
    {
        DrawCircleV(m_pos, m_radius, m_color);
    }
    else
    {
        DrawCircleLines((int)m_pos.x, (int)m_pos.y, m_radius, m_color);
    }

    rlPopMatrix();
}

raylib::Vector2 &CircleRenderer::GetPos()
{
    return m_pos;
}