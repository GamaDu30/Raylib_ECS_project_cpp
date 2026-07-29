#pragma once

#include "global/definitions.hpp"
#include "list"

class GameObject;

class ComponentBase
{
protected:
    GameObject *m_owner;
    bool m_isDirty;

public:
    ComponentBase();
    virtual ~ComponentBase();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    GameObject *GetOwner();
};