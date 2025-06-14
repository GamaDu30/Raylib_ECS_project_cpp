#include "components/Collider/CircleCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"

CircleCollider::CircleCollider(raylib::Vector2 offset, float radius)
{
    m_offset = offset;
    m_radius = radius;
}

CircleCollider::~CircleCollider()
{
}

void CircleCollider::Init(GameObject *owner)
{
    ColliderComponent::Init(owner);
}

void CircleCollider::Update()
{
}

void CircleCollider::Destroy()
{
}

void CircleCollider::IsColliding(ColliderComponent *other)
{
    other->IsColliding(this);
}

void CircleCollider::IsColliding(CircleCollider *other)
{
    float d = other->m_owner->GetTransform()->GetPos().Distance(this->m_owner->GetTransform()->GetPos());
    ColliderComponent::HandleCollisionState(d <= m_radius + other->m_radius, other);
}

void CircleCollider::IsColliding(RectCollider *other)
{
}