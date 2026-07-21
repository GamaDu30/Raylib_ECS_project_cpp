#pragma once

#include "components/Renderer/UI/UIRenderComponent.hpp"

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

class GameObject;

class ImageRenderer : public UIRenderComponent
{
    std::string m_textureName;

    ImageType m_imageType = ImageType::Simple;
    FillMethod m_fillMethod = FillMethod::Horizontal;
    float m_fillAmount = 1.0f;

public:
    ImageRenderer(std::string textureName = "");
    ~ImageRenderer();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    void SetImageType(ImageType type);
    void SetFillMethod(FillMethod method);
    void SetFillAmount(float amount);

    void Render() override;
};