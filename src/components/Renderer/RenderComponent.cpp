#include "components/Renderer/RenderComponent.hpp"
#include "components/TransformComponent.hpp"
#include "global/gameObject.hpp"

std::vector<RenderComponent *> RenderComponent::m_renderers = {};

RenderComponent::RenderComponent(Anchor anchor = Anchor::Center, raylib::Vector2 offset = raylib::Vector2(), raylib::Color color = WHITE)
{
    m_anchor = anchor;
    m_offset = offset;
    m_color = color;
    m_renderers.push_back(this);
}

void RenderComponent::Init(GameObject *owner)
{
    Component::Init(owner);
}

void RenderComponent::Update()
{
    Component::Update();
}

void RenderComponent::Destroy()
{
    Component::Destroy();
}

void RenderComponent::Render()
{
    TransformComponent *transform = m_owner->GetTransform();

    if (transform == nullptr)
    {
        TraceLog(LOG_ERROR, "RenderComponent doesn't have access to the TransformComponent");
        return;
    }

    transform->PushMatrix();
}

void RenderComponent::SetColor(raylib::Color color)
{
    m_color = color;
}