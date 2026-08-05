#include "components/Renderer/UI/ImageComponent.hpp"
#include "global/Sprites.hpp"
#include "components/RectTransformComponent.hpp"
#include "global/gameObject.hpp"
#include "ImageComponent.hpp"

ImageComponent::ImageComponent(ImageData data)
{
    m_imageData = data;
    if (m_imageData.textureName != "")
    {
        Sprites::GetSprite(this, m_imageData.textureName);
    }
}

ImageComponent::~ImageComponent()
{
}

void ImageComponent::Init(GameObject *owner)
{
    UIRenderComponent::Init(owner);
}

void ImageComponent::OnUpdate()
{
    UIRenderComponent::OnUpdate();
}

void ImageComponent::Destroy()
{
    UIRenderComponent::Destroy();
}

void ImageComponent::SetImageType(ImageType type)
{
    m_imageData.imageType = type;
}

void ImageComponent::SetFillAmount(float amount)
{
    m_fillAmount = std::clamp(amount, 0.0f, 1.0f);
}

void ImageComponent::SetImageFillData(const ImageFillData data)
{
    m_imageData.fillData = data;
}

void ImageComponent::Render()
{
    raylib::Texture2D *texture = Sprites::GetSprite(this, m_imageData.textureName);
    raylib::Rectangle source = raylib::Rectangle(0, 0, texture->GetWidth(), texture->GetHeight());
    raylib::Rectangle worldRect = m_rectTransformComp->GetWorldRectangle();
    raylib::Rectangle dest = worldRect;

    if (m_imageData.imageType == ImageType::Filled)
    {
        switch (m_imageData.fillData.method)
        {
        case FillMethod::Horizontal:
            source.width *= m_fillAmount;
            dest.width *= m_fillAmount;

            if (m_imageData.fillData.inverseFillDirection)
            {
                dest.x += worldRect.width * (1 - m_fillAmount);
                dest.width = worldRect.width * m_fillAmount;

                source.x = texture->width * (1 - m_fillAmount);
            }
            break;
        case FillMethod::Vertical:
            source.height *= m_fillAmount;
            dest.height *= m_fillAmount;

            if (m_imageData.fillData.inverseFillDirection)
            {
                dest.y += worldRect.height * (1 - m_fillAmount);
                dest.height = worldRect.height * m_fillAmount;

                source.y = texture->height * (1 - m_fillAmount);
            }
            break;
        case FillMethod::Radial360:
            // Radial fill logic can be implemented here
            break;
        }
    }

    DrawTexturePro(*texture, source, dest, raylib::Vector2(0, 0), m_rectTransformComp->GetRotation(), m_color);
}