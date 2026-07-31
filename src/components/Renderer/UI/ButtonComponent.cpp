#include "components/Renderer/UI/ButtonComponent.hpp"
#include "ButtonComponent.hpp"

ButtonComponent::ButtonComponent()
{
    m_state = ButtonState::NORMAL;
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::Init(GameObject *owner)
{
    UIRenderComponent::Init(owner);
}

void ButtonComponent::Update()
{
    UIRenderComponent::Update();
}

void ButtonComponent::Destroy()
{
    UIRenderComponent::Destroy();
}

void ButtonComponent::Render()
{
    raylib::Rectangle collision = GetCollision();
    collision.Draw(m_colors[static_cast<int>(m_state)]);
}

void ButtonComponent::SetOnClickCallback(std::function<void()> callback)
{
    m_onClickCallback = callback;
}

void ButtonComponent::SetOnReleaseCallback(std::function<void()> callback)
{
    m_onReleaseCallback = callback;
}

void ButtonComponent::ApplyClickCallback()
{
    if (m_onClickCallback)
    {
        m_onClickCallback();
    }

    SetState(ButtonState::PRESSED);
}

void ButtonComponent::ApplyReleaseCallback()
{
    if (m_onReleaseCallback)
    {
        m_onReleaseCallback();
    }

    SetState(ButtonState::HOVERED);
}

void ButtonComponent::SetState(ButtonState state)
{
    m_state = state;
}