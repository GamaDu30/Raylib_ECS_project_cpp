#pragma once

#include "components/Renderer/UI/UIRenderComponent.hpp"
#include "components/Renderer/UI/TextComponent.hpp"
#include "components/Renderer/UI/ImageComponent.hpp"
#include <functional>

class ImageComponent;
class TextComponent;

enum class ButtonState
{
    NORMAL,
    HOVERED,
    PRESSED,
    DISABLED,
    TOTAL
};

class ButtonComponent : public UIRenderComponent
{
    ButtonState m_state = ButtonState::NORMAL;

    ImageData m_imageData;
    TextData m_textData;

    ImageComponent *m_imageComp = nullptr;
    TextComponent *m_textComp = nullptr;

    // TEMP
    raylib::Color m_colors[static_cast<int>(ButtonState::TOTAL)] = {
        raylib::Color(255, 255, 255, 255), // NORMAL
        raylib::Color(200, 200, 200, 255), // HOVERED
        raylib::Color(150, 150, 150, 255), // PRESSED
        raylib::Color(100, 100, 100, 255)  // DISABLED
    };

    std::function<void()> m_onClickCallback;
    std::function<void()> m_onReleaseCallback;

public:
    ButtonComponent(ImageData imageData = ImageData(), TextData textData = TextData());
    ~ButtonComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();
    virtual void Render();

    void SetOnClickCallback(std::function<void()> callback);
    void SetOnReleaseCallback(std::function<void()> callback);

    void ApplyClickCallback();
    void ApplyReleaseCallback();

    void SetState(ButtonState state);
    ButtonState GetState() const { return m_state; }
};