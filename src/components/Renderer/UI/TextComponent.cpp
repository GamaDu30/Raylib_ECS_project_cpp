#include "components/Renderer/UI/TextComponent.hpp"
#include "global/gameObject.hpp"
#include "components/Renderer/UI/TextComponent.hpp"
#include <bits/stdc++.h>
#include "TextComponent.hpp"

TextComponent::TextComponent(TextData data)
{
    m_text = data;
}

TextComponent::~TextComponent()
{
}

void TextComponent::Init(GameObject *owner)
{
    UIRenderComponent::Init(owner);

    Format();
}

void TextComponent::Update()
{
    UIRenderComponent::Update();
}

void TextComponent::Destroy()
{
    UIRenderComponent::Destroy();
}

// TODO: Manage text overflow with height
void TextComponent::Render()
{
    UIRenderComponent::Render();

    raylib::Rectangle collision = GetCollision();
    std::istringstream ss(m_formattedText);
    std::string line;
    int lineHeight = m_text.fontSize + 2;

    int lineCount = std::count(m_formattedText.begin(), m_formattedText.end(), '\n') + 1;
    int totalHeight = lineCount * lineHeight - 2;

    int y = collision.y;
    if (m_text.alignmentV == TextAlignmentV::MIDDLE)
        y = collision.y + (collision.height - totalHeight) / 2;
    else if (m_text.alignmentV == TextAlignmentV::BOTTOM)
        y = collision.y + collision.height - totalHeight;

    while (std::getline(ss, line))
    {
        int lineWidth = MeasureText(line.c_str(), m_text.fontSize);
        int x = collision.x;

        if (m_text.alignmentH == TextAlignmentH::CENTER)
            x = collision.x + (collision.width - lineWidth) / 2;
        else if (m_text.alignmentH == TextAlignmentH::RIGHT)
            x = collision.x + collision.width - lineWidth;

        raylib::DrawText(line.c_str(), x, y, m_text.fontSize, m_color);
        y += lineHeight;
    }
}

void TextComponent::Format()
{
    std::stringstream ss(m_text.text);
    std::string word = "";
    std::string curLine = "";
    float maxWidth = GetCollision().width;

    m_formattedText = "";

    // Split the text into lines based on the width of the RectTransformComponent
    while (ss >> word)
    {
        if (MeasureText((curLine + word).c_str(), m_text.fontSize) > maxWidth)
        {
            m_formattedText += curLine + "\n";
            curLine = word + " ";
        }
        else
        {
            curLine += word + " ";
        }
    }

    if (!curLine.empty())
        m_formattedText += curLine;

    if (!m_formattedText.empty() && m_formattedText.back() == ' ')
        m_formattedText.pop_back();
}

void TextComponent::SetText(std::string text)
{
    m_text.text = text;
    Format();
}

void TextComponent::SetAlignmentH(TextAlignmentH alignment)
{
    m_text.alignmentH = alignment;
    Format();
}

void TextComponent::SetAlignmentV(TextAlignmentV alignment)
{
    m_text.alignmentV = alignment;
    Format();
}