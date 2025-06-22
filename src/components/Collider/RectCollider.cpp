#include "components/Collider/RectCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "RectCollider.hpp"
#include "components/CameraComponent.hpp"
#include "components/Collider/CircleCollider.hpp"

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

CollisionInfo *RectCollider::GetColInfo()
{
    std::vector<raylib::Vector2> localPoints = {
        raylib::Vector2(),
        raylib::Vector2(m_size.x, 0),
        m_size,
        raylib::Vector2(0, m_size.y)};

    for (raylib::Vector2 &curPoint : localPoints)
    {
        curPoint -= m_size * 0.5f;
        curPoint = Vector2Transform(curPoint, m_owner->GetTransform()->GetMatrix());

        if (CameraComponent::GetMainCam() != nullptr)
        {
            curPoint = Vector2Transform(curPoint, CameraComponent::GetMainCam()->m_matrix);
        }
    }

    return new PolyColInfo(localPoints);
}

void RectCollider::IsColliding(ColliderComponent *other)
{
    other->IsColliding(this);
}

void RectCollider::IsColliding(RectCollider *other)
{
    bool isCol = ColPolyPoly(dynamic_cast<PolyColInfo *>(GetColInfo()), dynamic_cast<PolyColInfo *>(other->GetColInfo()));
    ColliderComponent::HandleCollisionState(isCol, other);
}

void RectCollider::IsColliding(CircleCollider *other)
{
    bool isCol = ColPolyCircle(dynamic_cast<PolyColInfo *>(this->GetColInfo()), dynamic_cast<CircleColInfo *>(other->GetColInfo()));
    ColliderComponent::HandleCollisionState(isCol, other);
}