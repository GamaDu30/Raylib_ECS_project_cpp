#include "global/gameObject.hpp"
#include "algorithm"
#include "components/ComponentBase.hpp"
#include "components/TransformComponent.hpp"
#include "components/Renderer/RenderComponent.hpp"
#include "components/Collider/ColliderComponent.hpp"
#include "components/Renderer/RectRenderer.hpp"
#include "gameObject.hpp"

unsigned int GameObject::m_curUID = 0;

GameObject::GameObject(std::string name)
{
    m_name = name;

    if (m_name == "")
    {
        m_name = "GameObject " + std::to_string(m_curUID);
    }

    m_curUID++;

    AddComponentInternal<TransformComponent>();

    m_isInit = true;
}

GameObject::~GameObject()
{
    for (int i = m_components.size() - 1; i >= 0; i--)
    {
        delete m_components[i];
    }

    m_components.clear();
}

std::string GameObject::GetName()
{
    return m_name;
}

TransformComponent *GameObject::GetTransform()
{
    return m_transformComp;
}

void GameObject::OnCollisionEnter(ColliderComponent *collider)
{
}

void GameObject::OnCollisionExit(ColliderComponent *collider)
{
}

void GameObject::SetActive(bool active)
{
    m_isActive = active;

    for (ComponentBase *component : m_components)
    {
        component->SetActive(active);
    }

    for (TransformComponent *child : GetTransform()->GetChildren())
    {
        child->GetOwner()->SetActive(active);
    }
}

void GameObject::Start()
{
}

void GameObject::Update()
{
    if (!m_isActive)
    {
        return;
    }

    for (ComponentBase *component : m_components)
    {
        component->Update();
    }
}