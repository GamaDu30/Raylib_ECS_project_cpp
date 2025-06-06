#pragma once

#include "global/definitions.hpp"

class GameObject;

class Component
{
protected:
    GameObject *m_owner;

public:
    Component();
    ~Component();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    GameObject *GetOwner();
};