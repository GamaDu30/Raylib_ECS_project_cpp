#include "global/gameObject.hpp"
#include "algorithm"
#include "components/TransformComponent.hpp"
#include "components/Renderer/RenderComponent.hpp"
#include "components/Collider/ColliderComponent.hpp"
#include "components/Renderer/RectRenderer.hpp"

unsigned int GameObject::m_curUID = 0;

GameObject::GameObject(std::string name)
{
    m_name = name;

    if (m_name == "")
    {
        m_name = "GameObject " + std::to_string(m_curUID);
    }

    m_curUID++;

    AddComponent<TransformComponent>();

    m_isInit = true;
}

GameObject::~GameObject()
{
    for (int i = m_components.size() - 1; i >= 0; i--)
    {
        delete m_components[i];
        m_components[i] = nullptr;
    }

    m_transformComp = nullptr;
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

void GameObject::Start()
{
}

void GameObject::Update()
{
    for (Component *component : m_components)
    {
        component->Update();
    }
}