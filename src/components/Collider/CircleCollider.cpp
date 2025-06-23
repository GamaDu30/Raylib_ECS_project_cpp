#include "components/Collider/CircleCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/Collider/RectCollider.hpp"
#include "components/CameraComponent.hpp"

CircleCollider::CircleCollider(float radius, raylib::Vector2 offset)
{
    m_offset = offset;
    m_radius = radius;
}

CircleCollider::~CircleCollider()
{
    ColliderComponent::~ColliderComponent();
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

CollisionInfo *CircleCollider::GetColInfo()
{
    return new CircleColInfo(GetPos(), m_radius);
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
    bool isCol = ColPolyCircle(dynamic_cast<PolyColInfo *>(other->GetColInfo()), dynamic_cast<CircleColInfo *>(this->GetColInfo()));
    ColliderComponent::HandleCollisionState(isCol, other);
}

void CircleCollider::DrawDebug()
{
    GetPos().DrawCircle(m_radius, raylib::Color(255, 0, 0, 95));
}