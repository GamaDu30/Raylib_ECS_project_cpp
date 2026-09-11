#include "components/Renderer/RenderComponent.hpp"
#include "components/TransformComponent.hpp"
#include "global/gameObject.hpp"
#include "algorithm"

RenderComponent::RenderComponent(Anchor anchor, raylib::Vector2 offset, raylib::Color color)
{
    m_anchor = anchor;
    m_offset = offset;
    m_color = color;
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::Init(GameObject *owner)
{
    RenderComponentBase::Init(owner);
}

void RenderComponent::OnUpdate()
{
}

void RenderComponent::Destroy()
{
    RenderComponentBase::Destroy();
}

void RenderComponent::OnRender()
{
    TransformComponent *transform = m_owner->GetTransform();

    if (transform != nullptr)
    {
        transform->PushMatrix();
    }
}