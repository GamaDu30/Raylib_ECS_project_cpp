#include "components/Collider/ColliderComponent.hpp"
#include "algorithm"

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