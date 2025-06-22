#pragma once

#include "global/definitions.hpp"
#include "components/component.hpp"

class TransformComponent;
class ColliderComponent;

class GameObject
{
    static unsigned int m_curUID;
    static GameObject *Find(std::string name);

    std::string m_name;
    std::vector<Component *> m_components = {};

    TransformComponent *m_transformComp;

    bool m_isInit = false;

protected:
public:
    GameObject(std::string name = "");
    virtual ~GameObject();

    virtual void Start();
    virtual void Update();
    void Render();

    template <typename... Components>
    void AddComponents();
    template <typename T, typename... Args>
    T *AddComponent(Args &&...args);
    template <typename T>
    T *GetComponent();

    std::string GetName();
    TransformComponent *GetTransform();

    virtual void OnCollisionEnter(ColliderComponent *collider);
    virtual void OnCollisionExit(ColliderComponent *collider);
};

template <typename... Components>
inline void GameObject::AddComponents()
{
    (GameObject::AddComponent<Components>(), ...);
}

template <typename T, typename... Args>
T *GameObject::AddComponent(Args &&...args)
{
    static_assert(std::is_base_of_v<Component, T>, "(GameObject::AddComponent) T must inherit from Component");

    T *newComponent = new T(std::forward<Args>(args)...);

    if constexpr (std::is_same_v<T, TransformComponent>)
    {
        if (m_isInit)
        {
            TraceLog(LOG_ERROR, "You can't add a TransformComponent to a GameObject");
            return nullptr;
        }

        m_transformComp = newComponent;
    }

    // TODO: See in the future if needed
    for (auto curComponent : m_components)
    {
        if (typeid(*curComponent) == typeid(*newComponent))
        {
            TraceLog(LOG_WARNING, "You tried adding a component already present on this gameobject");

            delete newComponent;
            return nullptr;
        }
    }

    newComponent->Init(this);
    m_components.push_back(newComponent);

    return newComponent;
}

template <typename T>
T *GameObject::GetComponent()
{
    for (Component *comp : m_components)
    {
        if (T *casted = dynamic_cast<T *>(comp))
        {
            return casted;
        }
    }

    return nullptr;
}