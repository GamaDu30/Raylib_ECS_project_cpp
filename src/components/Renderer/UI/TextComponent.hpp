#pragma once

#include "components/Renderer/UI/UIRenderComponent.hpp"

enum class TextAlignmentH
{
    LEFT,
    CENTER,
    RIGHT
};

enum class TextAlignmentV
{
    TOP,
    MIDDLE,
    BOTTOM
};

struct TextData
{
    std::string text = "";
    int fontSize = 20;
    TextAlignmentH alignmentH = TextAlignmentH::LEFT;
    TextAlignmentV alignmentV = TextAlignmentV::TOP;
};

class TextComponent : public UIRenderComponent
{
    TextData m_text;
    std::string m_formattedText = "";

public:
    TextComponent(TextData data);
    ~TextComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();
    virtual void Render();

    void Format();
    void SetText(std::string text);
    void SetAlignmentH(TextAlignmentH alignment);
    void SetAlignmentV(TextAlignmentV alignment);
};