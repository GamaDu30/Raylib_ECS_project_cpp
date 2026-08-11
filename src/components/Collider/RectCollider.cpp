#include "components/Collider/RectCollider.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"
#include "RectCollider.hpp"
#include "components/CameraComponent.hpp"
#include "components/Collider/CircleCollider.hpp"
#include <memory>

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

void RectCollider::OnUpdate()
{
    ColliderComponent::OnUpdate();
}

void RectCollider::Destroy()
{
    ColliderComponent::Destroy();
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
    std::unique_ptr<CollisionInfo> thisInfo(GetColInfo());
    std::unique_ptr<CollisionInfo> otherInfo(other->GetColInfo());

    bool isCol = ColPolyPoly(
        dynamic_cast<PolyColInfo *>(thisInfo.get()),
        dynamic_cast<PolyColInfo *>(otherInfo.get()));

    ColliderComponent::HandleCollisionState(isCol, other);
}

void RectCollider::IsColliding(CircleCollider *other)
{
    std::unique_ptr<CollisionInfo> thisInfo(this->GetColInfo());
    std::unique_ptr<CollisionInfo> otherInfo(other->GetColInfo());

    bool isCol = ColPolyCircle(
        dynamic_cast<PolyColInfo *>(thisInfo.get()),
        dynamic_cast<CircleColInfo *>(otherInfo.get()));

    ColliderComponent::HandleCollisionState(isCol, other);
}

void RectCollider::DrawDebug()
{
    std::unique_ptr<CollisionInfo> colInfoPtr(GetColInfo());
    PolyColInfo *colInfo = static_cast<PolyColInfo *>(colInfoPtr.get());

    for (int i = 0; i < colInfo->points.size(); i++)
    {
        colInfo->points[i].DrawLine(colInfo->points[(i + 1) % colInfo->points.size()], 2.5f, m_debugColor);
    }
}