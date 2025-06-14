#include "components/Collider/ColliderComponent.hpp"

class CircleCollider : public ColliderComponent
{
    float m_radius;

protected:
    virtual void IsColliding(ColliderComponent *collider);
    virtual void IsColliding(CircleCollider *circle);

public:
    CircleCollider(raylib::Vector2 pos, float radius);
    ~CircleCollider();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();
};