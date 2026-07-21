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

void ImageRenderer::SetImageType(ImageType type)
{
    m_imageType = type;
}

void ImageRenderer::SetFillMethod(FillMethod method)
{
    m_fillMethod = method;
}

void ImageRenderer::SetFillAmount(float amount)
{
    m_fillAmount = std::clamp(amount, 0.0f, 1.0f);
}

void ImageRenderer::Render()
{
    raylib::Texture2D *texture = Sprites::GetSprite(this, m_textureName);
    raylib::Rectangle source = raylib::Rectangle(0, 0, texture->GetWidth(), texture->GetHeight());
    raylib::Rectangle dest = m_rectTransformComp->GetWorldRectangle();

    if (m_imageType == ImageType::Filled)
    {
        switch (m_fillMethod)
        {
        case FillMethod::Horizontal:
            source.width *= m_fillAmount;
            dest.width *= m_fillAmount;
            break;
        case FillMethod::Vertical:
            source.height *= m_fillAmount;
            dest.height *= m_fillAmount;
            break;
        case FillMethod::Radial360:
            // Radial fill logic can be implemented here
            break;
        }
    }

    DrawTexturePro(*texture, source, dest, raylib::Vector2(0, 0), m_rectTransformComp->GetRotation(), m_color);
}