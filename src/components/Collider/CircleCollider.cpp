#include "components/Collider/CircleCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/Collider/RectCollider.hpp"
#include "components/CameraComponent.hpp"
#include <memory>

CircleCollider::CircleCollider(float radius, raylib::Vector2 offset)
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

void CircleCollider::OnUpdate()
{
}

void CircleCollider::Destroy()
{
    ColliderComponent::Destroy();
}

CollisionInfo *CircleCollider::GetColInfo()
{
    return new CircleColInfo(GetPos(), m_radius * m_owner->GetTransform()->GetScale().x);
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
    std::unique_ptr<CollisionInfo> otherInfo(other->GetColInfo());
    std::unique_ptr<CollisionInfo> thisInfo(this->GetColInfo());

    bool isCol = ColPolyCircle(
        dynamic_cast<PolyColInfo *>(otherInfo.get()),
        dynamic_cast<CircleColInfo *>(thisInfo.get()));

    ColliderComponent::HandleCollisionState(isCol, other);
}

void CircleCollider::DrawDebug()
{
    std::unique_ptr<CollisionInfo> colInfoPtr(GetColInfo());
    CircleColInfo *colInfo = static_cast<CircleColInfo *>(colInfoPtr.get());
    colInfo->pos.DrawCircle(colInfo->radius, m_debugColor);
}