#include "components/Renderer/RenderComponent.hpp"
#include "components/TransformComponent.hpp"
#include "global/gameObject.hpp"
#include "algorithm"

std::vector<RenderComponent *> RenderComponent::m_renderers = {};

RenderComponent::RenderComponent(Anchor anchor = Anchor::Center, raylib::Vector2 offset = raylib::Vector2(), raylib::Color color = WHITE)
{
    m_anchor = anchor;
    m_offset = offset;
    m_color = color;
    m_renderers.push_back(this);
}

RenderComponent::~RenderComponent()
{
    m_renderers.erase(std::remove(m_renderers.begin(), m_renderers.end(), this), m_renderers.end());
}

void RenderComponent::RenderAll()
{
    std::sort(m_renderers.begin(), m_renderers.end(),
              [](RenderComponent *a, RenderComponent *b)
              {
                  return a->m_owner->GetTransform()->GetPos().z < b->m_owner->GetTransform()->GetPos().z;
              });

    for (RenderComponent *renderComp : m_renderers)
    {
        renderComp->Render();
    }
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

    if (transform != nullptr)
    {
        transform->PushMatrix();
    }
}

void RenderComponent::SetColor(raylib::Color color)
{
    m_color = color;
}