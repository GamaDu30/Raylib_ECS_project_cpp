#include "components/Renderer/UI/UIRenderComponent.hpp"
#include "components/RectTransformComponent.hpp"
#include "global/gameObject.hpp"

UIRenderComponent::UIRenderComponent()
{
}

UIRenderComponent::~UIRenderComponent()
{
}

void UIRenderComponent::Init(GameObject *owner)
{
    Component::Init(owner);

    m_rectTransformComp = m_owner->GetComponent<RectTransformComponent>();
}

void UIRenderComponent::Update()
{
}

void UIRenderComponent::Destroy()
{
}

void UIRenderComponent::Render()
{
}
