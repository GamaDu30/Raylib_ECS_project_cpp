#include "components/Renderer/SpriteRenderer.hpp"
#include "components/TransformComponent.hpp"
#include "global/gameObject.hpp"

SpriteRenderer::SpriteRenderer(std::string fileLocation, Anchor anchor, raylib::Color color, raylib::Vector2 offset) : RenderComponent::RenderComponent(anchor, offset, color)
{
    m_texture = LoadTexture(fileLocation.c_str());
}

void SpriteRenderer::Init(GameObject *owner)
{
    RenderComponent::Init(owner);
}

void SpriteRenderer::Update()
{
    RenderComponent::Update();
}

void SpriteRenderer::Destroy()
{
    RenderComponent::Update();
}

void SpriteRenderer::Render()
{
    RenderComponent::Render();

    raylib::Vector2 offset = GetAnchorOffset(m_anchor);

    rlTranslatef(
        -m_texture.width * offset.x,
        -m_texture.height * offset.y,
        0);

    m_texture.Draw();

    rlPopMatrix();
}