#include "components/Renderer/UI/UIRenderComponent.hpp"
#include "components/RectTransformComponent.hpp"
#include "global/gameObject.hpp"
#include "UIRenderComponent.hpp"

UIRenderComponent::UIRenderComponent()
{
}

UIRenderComponent::~UIRenderComponent()
{
}

void UIRenderComponent::Init(GameObject *owner)
{
    RenderComponentBase::Init(owner);

    m_rectTransformComp = m_owner->GetComponent<RectTransformComponent>();
}

void UIRenderComponent::OnUpdate()
{
}

void UIRenderComponent::Destroy()
{
}

void UIRenderComponent::OnRender()
{
}

raylib::Rectangle UIRenderComponent::GetCollision()
{
    if (m_rectTransformComp)
    {
        return m_rectTransformComp->GetWorldRectangle();
    }

    return raylib::Rectangle(0, 0, 0, 0);
}