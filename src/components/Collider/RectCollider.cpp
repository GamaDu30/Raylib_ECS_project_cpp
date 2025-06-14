#include "components/Collider/RectCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"

RectCollider::RectCollider(raylib::Vector2 size, raylib::Vector2 offset)
{
    m_offset = offset;
    m_size = size;
}

RectCollider::~RectCollider()
{
}

void RectCollider::Init(GameObject *owner)
{
    ColliderComponent::Init(owner);
}

void RectCollider::Update()
{
}

void RectCollider::Destroy()
{
}

void RectCollider::IsColliding(ColliderComponent *other)
{
    other->IsColliding(this);
}

void RectCollider::IsColliding(RectCollider *other)
{
    raylib::Vector2 selfPos = GetPos();
    raylib::Vector2 otherPos = other->GetPos();
    raylib::Vector2 otherSize = other->m_size;

    bool isCol = !((otherPos.x + otherSize.x <= selfPos.x) ||
                   (selfPos.x + m_size.x <= otherPos.x) ||
                   (otherPos.y + otherSize.y <= selfPos.y) ||
                   (selfPos.y + m_size.y <= otherPos.y));

    ColliderComponent::HandleCollisionState(isCol, other);
}

void RectCollider::IsColliding(CircleCollider *other)
{
}