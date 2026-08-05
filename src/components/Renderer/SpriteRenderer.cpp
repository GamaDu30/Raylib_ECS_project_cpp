#include "components/Renderer/SpriteRenderer.hpp"
#include "components/TransformComponent.hpp"
#include "global/gameObject.hpp"
#include "global/Sprites.hpp"

SpriteRenderer::SpriteRenderer(std::string fileLocation, Anchor anchor, raylib::Color color, raylib::Vector2 offset) : RenderComponent::RenderComponent(anchor, offset, color)
{
    m_textureName = fileLocation;

    Sprites::GetSprite(this, m_textureName);
}

SpriteRenderer::~SpriteRenderer()
{
    Sprites::OnRendererDeleted(this);
}

void SpriteRenderer::Init(GameObject *owner)
{
    RenderComponent::Init(owner);
}

void SpriteRenderer::OnUpdate()
{
    RenderComponent::OnUpdate();
}

void SpriteRenderer::Destroy()
{
    RenderComponent::Destroy();
}

void SpriteRenderer::OnRender()
{
    raylib::Vector2 offset = GetAnchorOffset(m_anchor);
    raylib::Texture2D *texture = Sprites::GetSprite(this, m_textureName);

    rlTranslatef(
        -texture->width * offset.x,
        -texture->height * offset.y,
        0);

    texture->Draw(raylib::Vector2(0, 0), m_color);

    rlPopMatrix();
}

raylib::Texture2D *SpriteRenderer::GetTexture()
{
    return Sprites::GetSprite(this, m_textureName);
}