#pragma once

#include "components/Collider/ColliderComponent.hpp"

class CircleCollider : public ColliderComponent
{
    float m_radius;

protected:
    virtual CollisionManifold IsColliding(ColliderComponent *other);
    virtual CollisionManifold IsColliding(CircleCollider *other);
    virtual CollisionManifold IsColliding(RectCollider *other);

public:
    CircleCollider(float radius, raylib::Vector2 offset = raylib::Vector2());
    ~CircleCollider();

    virtual CollisionInfo *GetColInfo() override;
    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    virtual void DrawDebug() override;
};