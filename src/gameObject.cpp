#include "gameObject.hpp"
#include "algorithm"
#include "components/TransformComponent.hpp"
#include "components/RenderComponent.hpp"

std::vector<GameObject *> GameObject::m_gameObjects = {};
unsigned int GameObject::m_curUID = 0;

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
    m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), this), m_gameObjects.end());
}

std::string GameObject::GetName()
{
    return m_name;
}

TransformComponent *GameObject::GetTransform()
{
    return m_transform;
}

void GameObject::Update()
{
    for (auto component : m_components)
    {
        component->Update();
    }
}

void GameObject::UpdateAll()
{
    for (auto gameObject : m_gameObjects)
    {
        gameObject->Update();
    }
}

void GameObject::Render()
{
    for (auto curComponent : m_components)
    {
        RenderComponent *renderComponent = dynamic_cast<RenderComponent *>(curComponent);

        if (renderComponent != nullptr)
        {
            renderComponent->Render();
        }
    }
}

void GameObject::RenderAll()
{
    std::sort(m_gameObjects.begin(), m_gameObjects.end(),
              [](GameObject *a, GameObject *b)
              {
                  return a->GetTransform()->GetPos().z < b->GetTransform()->GetPos().z;
              });

    for (auto gameObject : m_gameObjects)
    {
        gameObject->Render();
        TraceLog(LOG_DEBUG, (gameObject->GetName() + " z: %f").c_str(), gameObject->GetTransform()->GetPos().z);
    }

    TraceLog(LOG_DEBUG, "");
}
