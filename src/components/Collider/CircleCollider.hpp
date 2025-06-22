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
    CircleCollider(float radius, raylib::Vector2 offset = raylib::Vector2());
    ~CircleCollider();

    virtual CollisionInfo *GetColInfo() override;
    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
};