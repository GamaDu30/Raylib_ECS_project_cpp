#pragma once

#include "components/Collider/ColliderComponent.hpp"

class RectCollider : public ColliderComponent
{
    raylib::Vector2 m_size;

protected:
    virtual void IsColliding(ColliderComponent *other);
    virtual void IsColliding(RectCollider *other);
    virtual void IsColliding(CircleCollider *other);

public:
    RectCollider(raylib::Vector2 size, raylib::Vector2 offset = raylib::Vector2());
    ~RectCollider();

    virtual CollisionInfo *GetColInfo() override;
    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
};