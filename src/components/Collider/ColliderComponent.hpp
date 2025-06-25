#pragma once

#include "components/Component.hpp"

class CircleCollider;
class RectCollider;

class ColliderComponent : public Component
{
    static std::vector<ColliderComponent *> m_colliders;
    static unsigned int m_curUID;
    std::vector<unsigned int> m_collidersCompId;

protected:
    raylib::Vector2 m_offset;
    unsigned int m_UID;

public:
    ColliderComponent();
    ~ColliderComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual CollisionInfo *GetColInfo() = 0;

    static void CheckCollisions();
    // TODO create sub classes
    virtual void IsColliding(ColliderComponent *other) = 0;
    virtual void IsColliding(CircleCollider *other) = 0;
    virtual void IsColliding(RectCollider *other) = 0;

    raylib::Vector2 GetPos();

    void HandleCollisionState(bool curColState, ColliderComponent *other);

    static void DrawAllDebug();
    virtual void DrawDebug() = 0;
};