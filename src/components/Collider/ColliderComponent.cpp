#include "components/Collider/ColliderComponent.hpp"
#include "algorithm"
#include <chrono>
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"

unsigned int ColliderComponent::m_curUID = 0;

ColliderComponent::ColliderComponent()
{
    m_UID = m_curUID++;
    m_collidersCompId = std::vector<unsigned int>();
    m_debugColor = raylib::Color(255, 0, 0, 95);
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Init(GameObject *owner)
{
    Component::Init(owner);
}

void ColliderComponent::OnUpdate()
{
}

void ColliderComponent::Destroy()
{
    Component::Destroy();
}

void ColliderComponent::CheckCollisions()
{
    auto colliders = ComponentBase::GetInstancesAssignable<ColliderComponent>();

    for (size_t i = 0; i < colliders.size(); i++)
    {
        for (size_t j = i + 1; j < colliders.size(); j++)
        {
            colliders[i]->IsColliding(colliders[j]);
        }
    }
}

raylib::Vector2 ColliderComponent::GetPos()
{
    raylib::Vector2 pos = raylib::Vector2(
        m_owner->GetTransform()->GetPos().x + m_offset.x * 2,
        m_owner->GetTransform()->GetPos().y + m_offset.y * 2);

    return Vector2Transform(pos, CameraComponent::GetMainCam()->m_matrix);
}

void ColliderComponent::HandleCollisionState(bool curColState, ColliderComponent *other)
{
    // Check if Collider UID is already in vector (this means they're already colliding)
    bool isCurrentlyColliding = std::find(m_collidersCompId.begin(), m_collidersCompId.end(), other->m_UID) != m_collidersCompId.end();

    if (!isCurrentlyColliding && curColState)
    {
        m_collidersCompId.push_back(other->m_UID);
        this->m_owner->OnCollisionEnter(other);
        m_debugColor = raylib::Color(0, 255, 0, 95);
    }
    else if (isCurrentlyColliding && !curColState)
    {
        m_collidersCompId.erase(std::remove(m_collidersCompId.begin(), m_collidersCompId.end(), other->m_UID), m_collidersCompId.end());
        this->m_owner->OnCollisionExit(other);
        m_debugColor = raylib::Color(255, 0, 0, 95);
    }
}