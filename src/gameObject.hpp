#pragma once

#include "definitions.hpp"
#include "components/component.hpp"

class TransformComponent;

class GameObject
{
    static std::vector<GameObject *> m_gameObjects;
    static unsigned int m_curUID;

    std::string m_name;
    std::vector<Component *> m_components = {};

    TransformComponent *m_transform;

    bool m_isInit = false;

protected:
    void Update();
    void Render();

public:
    GameObject(std::string name = "");
    ~GameObject();

    static void UpdateAll();
    static void RenderAll();

    template <typename... Components>
    void AddComponents();
    template <typename T>
    void AddComponent();
    template <typename T>
    T *GetComponent();

    std::string GetName();
    TransformComponent *GetTransform();
};

template <typename... Components>
inline void GameObject::AddComponents()
{
    (GameObject::AddComponent<Components>(), ...);
}

template <typename T>
void GameObject::AddComponent()
{
    T *newComponent = new T();

    if constexpr (std::is_same_v<T, TransformComponent>)
    {
        if (m_isInit)
        {
            TraceLog(LOG_ERROR, "You can't add a TransformComponent to a GameObject");
            return;
        }

        m_transform = newComponent;
    }

    for (auto curComponent : m_components)
    {
        if (typeid(*curComponent) == typeid(*newComponent))
        {
            TraceLog(LOG_WARNING, "You tried adding a component already present on this gameobject");
            return;
        }
    }

    newComponent->Init(this);
    m_components.push_back(newComponent);
}