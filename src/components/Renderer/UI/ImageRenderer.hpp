#pragma once

#include "components/Renderer/UI/UIRenderComponent.hpp"

class GameObject;

class ImageRenderer : public UIRenderComponent
{
    std::string m_textureName;

public:
    ImageRenderer(std::string textureName = "");
    ~ImageRenderer();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    void Render() override;
};