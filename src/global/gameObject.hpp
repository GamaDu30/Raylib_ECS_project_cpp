#pragma once

#include "global/definitions.hpp"
#include "components/Component.hpp"
#include "components/TransformComponent.hpp"

class RectTransformComponent;
class ColliderComponent;

class GameObject
{
    static unsigned int m_curUID;

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

    template <typename... Components>
    void AddComponents();
    template <typename T, typename... Args>
    T *AddComponent(Args &&...args);
    template <typename T>
    T *GetComponent();
    template <typename T>
    void RemoveComponent();

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

    m_components.push_back(newComponent);
    newComponent->Init(this);

    return newComponent;
}

template <typename T>
T *GameObject::GetComponent()
{
    for (Component *comp : m_components)
    {
        if (T *castedComp = dynamic_cast<T *>(comp))
        {
            return castedComp;
        }
    }

    return nullptr;
}

template <typename T>
inline void GameObject::RemoveComponent()
{
    Component *comp = GetComponent<T>();
    if (comp != nullptr)
    {
        m_components.erase(std::remove(m_components.begin(), m_components.end(), comp), m_components.end());
        delete comp;
        comp = nullptr;
    }
}
