#include "components/Renderer/UI/ImageRenderer.hpp"
#include "global/Sprites.hpp"
#include "components/RectTransformComponent.hpp"
#include "global/gameObject.hpp"

ImageRenderer::ImageRenderer(std::string textureName)
{
    if (textureName != "")
    {
        m_textureName = textureName;
        Sprites::GetSprite(this, m_textureName);
    }
}

ImageRenderer::~ImageRenderer()
{
}

void ImageRenderer::Init(GameObject *owner)
{
    UIRenderComponent::Init(owner);
}

void ImageRenderer::Update()
{
    UIRenderComponent::Update();
}

void ImageRenderer::Destroy()
{
    UIRenderComponent::Destroy();
}

void ImageRenderer::Render()
{
    raylib::Texture2D *texture = Sprites::GetSprite(this, m_textureName);
    raylib::Rectangle source = raylib::Rectangle(0, 0, texture->GetWidth(), texture->GetHeight());

    DrawTexturePro(*texture, source, m_rectTransformComp->GetWorldRectangle(), raylib::Vector2(0, 0), m_rectTransformComp->GetRotation(), WHITE);
}