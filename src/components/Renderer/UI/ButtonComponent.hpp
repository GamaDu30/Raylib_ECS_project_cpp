#pragma once

#include "components/Renderer/UI/UIRenderComponent.hpp"
#include <functional>

class ImageComponent;

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

    std::string m_sprite = "";
    std::string m_text = "";

    ImageComponent *m_imageComp = nullptr;

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
    ButtonComponent(std::string sprite = "", std::string text = "");
    ~ButtonComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
    virtual void Render();

    void SetOnClickCallback(std::function<void()> callback);
    void SetOnReleaseCallback(std::function<void()> callback);

    void ApplyClickCallback();
    void ApplyReleaseCallback();

    void SetState(ButtonState state);
    ButtonState GetState() const { return m_state; }
};