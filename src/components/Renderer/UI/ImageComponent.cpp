#include "components/Renderer/UI/ImageComponent.hpp"
#include "global/Sprites.hpp"
#include "components/RectTransformComponent.hpp"
#include "global/gameObject.hpp"
#include "ImageComponent.hpp"

ImageComponent::ImageComponent(std::string textureName)
{
    if (textureName != "")
    {
        m_textureName = textureName;
        Sprites::GetSprite(this, m_textureName);
    }
}

ImageComponent::~ImageComponent()
{
}

void ImageComponent::Init(GameObject *owner)
{
    UIRenderComponent::Init(owner);
}

void ImageComponent::Update()
{
    UIRenderComponent::Update();
}

void ImageComponent::Destroy()
{
    UIRenderComponent::Destroy();
}

void ImageComponent::SetImageType(ImageType type)
{
    m_imageType = type;
}

void ImageComponent::SetFillMethod(FillMethod method)
{
    m_fillMethod = method;
}

void ImageComponent::SetFillAmount(float amount)
{
    m_fillAmount = std::clamp(amount, 0.0f, 1.0f);
}

void ImageComponent::SetInverseFillDirection(bool inverse)
{
    m_inverseFillDirection = inverse;
}

void ImageComponent::SetImageFillData(const ImageFillData &data)
{
    if (data.method)
    {
        m_fillMethod = data.method.value();
    }
    if (data.fillAmount)
    {
        m_fillAmount = std::clamp(data.fillAmount.value(), 0.0f, 1.0f);
    }
    if (data.inverseFillDirection)
    {
        m_inverseFillDirection = data.inverseFillDirection.value();
    }
}

void ImageComponent::Render()
{
    raylib::Texture2D *texture = Sprites::GetSprite(this, m_textureName);
    raylib::Rectangle source = raylib::Rectangle(0, 0, texture->GetWidth(), texture->GetHeight());
    raylib::Rectangle worldRect = m_rectTransformComp->GetWorldRectangle();
    raylib::Rectangle dest = worldRect;

    if (m_imageType == ImageType::Filled)
    {
        switch (m_fillMethod)
        {
        case FillMethod::Horizontal:
            source.width *= m_fillAmount;
            dest.width *= m_fillAmount;

            if (m_inverseFillDirection)
            {
                dest.x += worldRect.width * (1 - m_fillAmount);
                dest.width = worldRect.width * m_fillAmount;

                source.x = texture->width * (1 - m_fillAmount);
            }
            break;
        case FillMethod::Vertical:
            source.height *= m_fillAmount;
            dest.height *= m_fillAmount;

            if (m_inverseFillDirection)
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