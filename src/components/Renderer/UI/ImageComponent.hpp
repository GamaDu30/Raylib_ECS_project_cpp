#pragma once

#include "components/Renderer/UI/UIRenderComponent.hpp"
#include <optional>

enum class ImageType
{
    Simple,
    Filled
};

enum class FillMethod
{
    Horizontal,
    Vertical,
    Radial360
};

struct ImageFillData
{
    FillMethod method = FillMethod::Horizontal;
    bool inverseFillDirection = false;
};

struct ImageData
{
    std::string textureName = "";
    ImageType imageType = ImageType::Simple;
    ImageFillData fillData = {.method = FillMethod::Horizontal, .inverseFillDirection = false};
    raylib::Vector2 size = raylib::Vector2(100, 100);
};

class GameObject;

class ImageComponent : public UIRenderComponent
{
    ImageData m_imageData;
    // std::string m_textureName;

    // ImageType m_imageType = ImageType::Simple;
    // FillMethod m_fillMethod = FillMethod::Horizontal;
    float m_fillAmount = 1.0f;
    // bool m_inverseFillDirection = false;
    // raylib::Vector2 m_size = raylib::Vector2(100, 100);

public:
    ImageComponent(ImageData data);
    ~ImageComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    void SetImageType(ImageType type);
    void SetFillAmount(float amount);

    void SetImageFillData(const ImageFillData data);

    void Render() override;
};