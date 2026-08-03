#include "components/Renderer/UI/ButtonComponent.hpp"

#include "global/gameObject.hpp"
#include "global/Scene.hpp"
#include "components/TransformComponent.hpp"

ButtonComponent::ButtonComponent(ImageData imageData, TextData textData)
{
    m_state = ButtonState::NORMAL;

    m_imageData = imageData;
    m_textData = textData;
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::Init(GameObject *owner)
{
    UIRenderComponent::Init(owner);

    GameObject *spriteGO = Scene::GetScene()->CreateGameObject("ButtonSprite");
    spriteGO->GetTransform()->SetParent(GetOwner()->GetTransform());

    if (m_imageData.textureName != "")
    {
        m_imageComp = spriteGO->AddComponent<ImageComponent>(m_imageData);
    }
    if (m_textData.text != "")
    {
        m_textComp = spriteGO->AddComponent<TextComponent>(m_textData);
    }
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

    if (m_imageComp)
    {
        m_imageComp->SetColor(m_colors[static_cast<int>(m_state)]);
    }
}