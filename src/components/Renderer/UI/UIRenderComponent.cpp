#include "components/Renderer/UI/UIRenderComponent.hpp"
#include "components/RectTransformComponent.hpp"
#include "global/gameObject.hpp"
#include "UIRenderComponent.hpp"

UIRenderComponent::UIRenderComponent()
{
}

UIRenderComponent::~UIRenderComponent()
{
    delete m_rectTransformComp;
    m_rectTransformComp = nullptr;
}

void UIRenderComponent::Init(GameObject *owner)
{
    Component::Init(owner);

    m_rectTransformComp = m_owner->GetComponent<RectTransformComponent>();
}

void UIRenderComponent::OnUpdate()
{
}

void UIRenderComponent::Destroy()
{
}

void UIRenderComponent::Render()
{
}

void UIRenderComponent::SetColor(raylib::Color color)
{
    m_color = color;
}

raylib::Rectangle UIRenderComponent::GetCollision()
{
    if (m_rectTransformComp)
    {
        return m_rectTransformComp->GetWorldRectangle();
    }

    return raylib::Rectangle(0, 0, 0, 0);
}
