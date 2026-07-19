#pragma once

#include "global/definitions.hpp"
#include "components/Component.hpp"
#include "components/TransformComponent.hpp"
#include "components/RectTransformComponent.hpp"
#include "components/Renderer/UI/CanvasComponent.hpp"

class ColliderComponent;

class GameObject
{
    static unsigned int m_curUID;

    std::string m_name;
    std::vector<Component *> m_components = {};

    TransformComponent *m_transformComp = nullptr;

    bool m_isInit = false;

    template <typename T, typename... Args>
    T *AddComponentInternal(Args &&...args);

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

    friend class TransformComponent;
    friend class CanvasComponent;
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
    static_assert(!std::is_base_of_v<TransformComponent, T>, "(GameObject::AddComponent) You can't manually add a TransformComponent to a Gameobject.");

    return AddComponentInternal<T>(std::forward<Args>(args)...);
}

template <typename T, typename... Args>
T *GameObject::AddComponentInternal(Args &&...args)
{
    T *newComponent = new T(std::forward<Args>(args)...);

    // TransformComponent and RectTransformComponent
    if constexpr (std::is_same_v<RectTransformComponent, T>)
    {
        if (m_transformComp)
        {
            TraceLog(LOG_INFO, "%s", typeid(*newComponent).name());
            newComponent->SetDataFromTransform(m_transformComp);
            RemoveComponent<TransformComponent>();
        }

        m_transformComp = newComponent;
    }
    else if constexpr (std::is_same_v<T, TransformComponent>)
    {
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
