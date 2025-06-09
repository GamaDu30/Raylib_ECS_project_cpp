#include "components/Renderer/RectRenderer.hpp"

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