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
    std::optional<FillMethod> method;
    std::optional<float> fillAmount;
    std::optional<bool> inverseFillDirection;
};

class GameObject;

class ImageComponent : public UIRenderComponent
{
    std::string m_textureName;

    ImageType m_imageType = ImageType::Simple;
    FillMethod m_fillMethod = FillMethod::Horizontal;
    float m_fillAmount = 1.0f;
    bool m_inverseFillDirection = false;
    raylib::Vector2 m_size = raylib::Vector2(100, 100);

public:
    ImageComponent(std::string textureName = "");
    ~ImageComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    void SetImageType(ImageType type);
    void SetFillMethod(FillMethod method);
    void SetFillAmount(float amount);
    void SetInverseFillDirection(bool inverse);

    void SetImageFillData(const ImageFillData &data);

    void Render() override;
};