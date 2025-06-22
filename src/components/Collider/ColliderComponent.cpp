#include "components/Collider/ColliderComponent.hpp"
#include "algorithm"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"

std::vector<ColliderComponent *> ColliderComponent::m_colliders = {};

ColliderComponent::ColliderComponent()
{
    m_colliders.push_back(this);
    m_isColliding = false;
}

ColliderComponent::~ColliderComponent()
{
    m_colliders.erase(std::remove(m_colliders.begin(), m_colliders.end(), this), m_colliders.end());
}

void ColliderComponent::Init(GameObject *owner)
{
    Component::Init(owner);
}

void ColliderComponent::Update()
{
    Component::Update();
}

void ColliderComponent::Destroy()
{
    Component::Destroy();
}

void ColliderComponent::CheckCollisions()
{
    for (ColliderComponent *col1 : m_colliders)
    {
        for (ColliderComponent *col2 : m_colliders)
        {
            if (col1 == col2)
            {
                continue;
            }

            col1->IsColliding(col2);
        }
    }
}

raylib::Vector2 ColliderComponent::GetPos()
{
    // TODO: Do test to see if *2 works (ex: Anchors)
    raylib::Vector2 pos = raylib::Vector2(
        m_owner->GetTransform()->GetPos().x + m_offset.x * 2,
        m_owner->GetTransform()->GetPos().y + m_offset.y * 2);

    return Vector2Transform(pos, CameraComponent::GetMainCam()->m_matrix);
}

void ColliderComponent::HandleCollisionState(bool curColState, ColliderComponent *other)
{
    if (curColState)
    {
        if (m_isColliding)
        {
            return;
        }

        m_isColliding = true;
        this->m_owner->OnCollisionEnter(other);
    }
    else if (m_isColliding)
    {
        m_isColliding = false;
        this->m_owner->OnCollisionExit(other);
    }
}

void ColliderComponent::DrawAllDebug()
{
    for (ColliderComponent *collider : m_colliders)
    {
        collider->DrawDebug();
    }
}