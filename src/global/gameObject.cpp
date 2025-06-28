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

void GameObject::Render()
{
    m_transformComp->PushMatrix();

    for (Component *curComponent : m_components)
    {
        RenderComponent *renderComponent = dynamic_cast<RenderComponent *>(curComponent);

        if (renderComponent != nullptr)
        {
            renderComponent->Render();
        }
    }

    DrawLineV(raylib::Vector2(), raylib::Vector2(0, -25), GREEN);
    DrawLineV(raylib::Vector2(), raylib::Vector2(25, 0), RED);

    rlPopMatrix();
}