#include "global/gameObject.hpp"
#include "algorithm"
#include "components/TransformComponent.hpp"
#include "components/Renderer/RenderComponent.hpp"
#include "components/Collider/ColliderComponent.hpp"
#include "components/Renderer/RectRenderer.hpp"

std::vector<GameObject *> GameObject::m_gameObjects = {};
unsigned int GameObject::m_curUID = 0;

GameObject *GameObject::Find(std::string name)
{
    for (GameObject *curGo : m_gameObjects)
    {
        if (curGo->GetName() == name)
        {
            return curGo;
        }
    }

    return nullptr;
}

GameObject::GameObject(std::string name)
{
    m_name = name;

    if (m_name == "")
    {
        m_name = "GameObject " + std::to_string(m_curUID);
    }

    m_curUID++;

    m_gameObjects.push_back(this);

    AddComponent<TransformComponent>();

    m_isInit = true;
    TraceLog(LOG_DEBUG, ("New GameObject named " + m_name).c_str());
}

GameObject::~GameObject()
{
    for (Component *component : m_components)
    {
        m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end());
    }

    m_components.erase(std::remove(m_components.begin(), m_components.end(), m_transformComp), m_components.end());
    m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), this), m_gameObjects.end());
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
    TraceLog(LOG_DEBUG, (m_name + " COL ENTER").c_str());
    GetComponent<RectRenderer>()->SetColor(RED);
}

void GameObject::OnCollisionExit(ColliderComponent *collider)
{
    TraceLog(LOG_DEBUG, (m_name + " COL EXIT").c_str());
    GetComponent<RectRenderer>()->SetColor(WHITE);
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