#include "components/Collider/CircleCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"

CircleCollider::CircleCollider(raylib::Vector2 pos, float radius)
{
    m_pos = pos;
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

void CircleCollider::IsColliding(ColliderComponent *collider)
{
    collider->IsColliding(this);
}

void CircleCollider::IsColliding(CircleCollider *circle)
{
    float d = circle->m_owner->GetTransform()->GetPos().Distance(this->m_owner->GetTransform()->GetPos());
    if (d <= m_radius + circle->m_radius)
    {
        if (m_isColliding)
        {
            return;
        }

        m_isColliding = true;
        this->m_owner->OnCollisionEnter(circle);
    }
    else if (m_isColliding)
    {
        m_isColliding = false;
        this->m_owner->OnCollisionExit(circle);
    }
}