#pragma once

#include "components/Collider/ColliderComponent.hpp"

class CircleCollider : public ColliderComponent
{
    float m_radius;

protected:
    virtual void IsColliding(ColliderComponent *other);
    virtual void IsColliding(CircleCollider *other);
    virtual void IsColliding(RectCollider *other);

public:
    CircleCollider(raylib::Vector2 offset, float radius);
    ~CircleCollider();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
};