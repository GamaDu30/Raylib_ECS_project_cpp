#pragma once

#include "global/definitions.hpp"
#include "list"

class GameObject;

class ComponentBase
{
protected:
    GameObject *m_owner;

    bool m_isDirty;
    bool m_isActive;

    virtual void OnUpdate() = 0;

public:
    ComponentBase();
    virtual ~ComponentBase();

    virtual void Init(GameObject *owner);
    void Update();
    virtual void Destroy();

    GameObject *GetOwner();

    void SetActive(bool active);
};