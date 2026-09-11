#pragma once

#include "global/definitions.hpp"
#include "list"
#include <typeindex>
#include <type_traits>
#include <unordered_map>
#include <vector>

class GameObject;

class ComponentBase
{
protected:
    static std::unordered_map<std::type_index, std::vector<ComponentBase *>> &GetRegistry();

    GameObject *m_owner;

    bool m_isDirty;
    bool m_isActive;
    bool m_isRegistered;
    std::type_index m_registeredConcreteType;

    int m_uid;
    static unsigned int m_curUID;

    void RegisterConcreteInstance();
    void UnregisterConcreteInstance();

    virtual void OnUpdate() = 0;
    virtual void OnFixedUpdate() = 0;

public:
    ComponentBase();
    virtual ~ComponentBase();

    virtual void Init(GameObject *owner);
    void Update();
    void FixedUpdate();
    virtual void Destroy();

    GameObject *GetOwner();

    void SetActive(bool active);

    unsigned int GetUID();

    template <typename T>
    static std::vector<T *> GetInstancesOfType()
    {
        static_assert(std::is_base_of_v<ComponentBase, T>, "(ComponentBase::GetInstancesOfType) T must inherit from ComponentBase");

        auto &registry = GetRegistry();
        auto it = registry.find(std::type_index(typeid(T)));
        if (it == registry.end())
        {
            return {};
        }

        std::vector<T *> instances;
        instances.reserve(it->second.size());

        for (ComponentBase *instance : it->second)
        {
            if (T *typedInstance = dynamic_cast<T *>(instance))
            {
                instances.push_back(typedInstance);
            }
        }

        return instances;
    }

    template <typename T>
    static std::vector<T *> GetInstancesAssignable()
    {
        static_assert(std::is_base_of_v<ComponentBase, T>, "(ComponentBase::GetInstancesAssignable) T must inherit from ComponentBase");

        std::vector<T *> instances;
        auto &registry = GetRegistry();

        for (const auto &[type, concreteInstances] : registry)
        {
            (void)type;

            for (ComponentBase *instance : concreteInstances)
            {
                if (T *typedInstance = dynamic_cast<T *>(instance))
                {
                    instances.push_back(typedInstance);
                }
            }
        }

        return instances;
    }
};
