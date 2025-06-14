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
    RectCollider(raylib::Vector2 size, raylib::Vector2 pos = raylib::Vector2());
    ~RectCollider();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
};