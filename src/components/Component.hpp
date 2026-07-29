#pragma once

#include "global/definitions.hpp"
#include "components/ComponentBase.hpp"
#include "list"

class GameObject;

template <typename T>
class Component : public ComponentBase
{
    static std::list<T *> m_compInstances;

public:
    Component() { m_compInstances.push_back(static_cast<T *>(this)); }
    virtual ~Component() { m_compInstances.remove(static_cast<T *>(this)); }

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
};

template <typename T>
std::list<T *> Component<T>::m_compInstances = {};

template <typename T>
void Component<T>::Init(GameObject *owner)
{
    ComponentBase::Init(owner);
}

template <typename T>
void Component<T>::Update()
{
    ComponentBase::Update();
}

template <typename T>
void Component<T>::Destroy()
{
    ComponentBase::Destroy();
}