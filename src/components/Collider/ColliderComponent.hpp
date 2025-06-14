#include "components/Component.hpp"

class CircleCollider;

class ColliderComponent : public Component
{
    static std::vector<ColliderComponent *> m_colliders;

protected:
    raylib::Vector2 m_pos;
    bool m_isColliding;

public:
    ColliderComponent();
    ~ColliderComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    static void CheckCollisions();
    // TODO create sub classes
    virtual void IsColliding(ColliderComponent *collider) = 0;
    virtual void IsColliding(CircleCollider *collider) = 0;
};

struct Collision
{
    ColliderComponent *collider;
};