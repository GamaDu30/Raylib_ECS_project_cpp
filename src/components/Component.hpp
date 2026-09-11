#pragma once

#include "global/definitions.hpp"
#include "components/ComponentBase.hpp"
#include "list"

class GameObject;

template <typename T>
class Component : public ComponentBase
{
public:
    Component() {}
    virtual ~Component() {}

    virtual void Init(GameObject *owner);
    virtual void Destroy();

    void OnFixedUpdate() override;
};

template <typename T>
void Component<T>::Init(GameObject *owner)
{
    ComponentBase::Init(owner);
}

template <typename T>
void Component<T>::Destroy()
{
    ComponentBase::Destroy();
}

template <typename T>
void Component<T>::OnFixedUpdate()
{
}
