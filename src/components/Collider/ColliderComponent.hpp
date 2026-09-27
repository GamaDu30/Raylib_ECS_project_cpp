#pragma once

#include "components/Component.hpp"

class CircleCollider;
class RectCollider;

struct CollisionManifold
{
    GameObject *object1;
    GameObject *object2;

    raylib::Vector2 normal;
    raylib::Vector2 contactPoint;
    float penetration;
};

class ColliderComponent : public Component<ColliderComponent>
{
    static unsigned int m_curUID;

protected:
    raylib::Vector2 m_offset;
    unsigned int m_UID;
    std::vector<unsigned int> m_collidersCompId;
    raylib::Color m_debugColor;

public:
    ColliderComponent();
    ~ColliderComponent();

    virtual void Init(GameObject *owner);
    virtual void OnUpdate();
    virtual void Destroy();

    virtual CollisionInfo *GetColInfo() = 0;

    static std::vector<CollisionManifold> GetAllCollisions();
    virtual CollisionManifold IsColliding(ColliderComponent *other) = 0;
    virtual CollisionManifold IsColliding(CircleCollider *other) = 0;
    virtual CollisionManifold IsColliding(RectCollider *other) = 0;

    raylib::Vector2 GetPos();

    void HandleCollisionState(bool curColState, ColliderComponent *other);

    virtual void DrawDebug() = 0;
};