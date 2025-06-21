#include "global/definitions.hpp"

#include "components/Collider/ColliderComponent.hpp"
#include "components/Collider/CircleCollider.hpp"
#include "components/Collider/RectCollider.hpp"
#include <array>

raylib::Vector2 GetAnchorOffset(Anchor anchor)
{
    switch (anchor)
    {
    case Anchor::TopLeft:
        return {0.0f, 0.0f};
    case Anchor::TopCenter:
        return {0.5f, 0.0f};
    case Anchor::TopRight:
        return {1.0f, 0.0f};
    case Anchor::CenterLeft:
        return {0.0f, 0.5f};
    case Anchor::Center:
        return {0.5f, 0.5f};
    case Anchor::CenterRight:
        return {1.0f, 0.5f};
    case Anchor::BottomLeft:
        return {0.0f, 1.0f};
    case Anchor::BottomCenter:
        return {0.5f, 1.0f};
    case Anchor::BottomRight:
        return {1.0f, 1.0f};
    }
    return {0.5f, 0.5f}; // fallback
}

bool ColCircleCircle(CircleColInfo *c1, CircleColInfo *c2)
{
    return c1->pos.DistanceSqr(c2->pos) < std::powf(c1->radius + c2->radius, 2);
}

bool ColPolyPoly(PolyColInfo *c1, PolyColInfo *c2)
{
    raylib::Vector2 rangeC1 = raylib::Vector2(__FLT_MAX__, -__FLT_MAX__);
    raylib::Vector2 rangeC2 = rangeC1;
    std::array<PolyColInfo *, 2> shapes = {c1, c2};

    for (int y = 0; y < shapes.size(); y++)
    {
        for (int i = 0; i < shapes[y]->points.size(); i++)
        {
            rangeC1 = raylib::Vector2(__FLT_MAX__, -__FLT_MAX__);
            rangeC2 = rangeC1;

            raylib::Vector2 curPoint = shapes[y]->points[i];
            raylib::Vector2 curVec = (shapes[y]->points[(i + 1) % shapes[y]->points.size()] - shapes[y]->points[i]).Normalize();
            raylib::Vector2 curNormal = raylib::Vector2(-curVec.y, curVec.x);

            for (raylib::Vector2 pointC1 : shapes[y]->points)
            {
                float dot = curNormal.DotProduct(pointC1);

                rangeC1.x = std::min(rangeC1.x, dot);
                rangeC1.y = std::max(rangeC1.y, dot);
            }

            for (raylib::Vector2 pointC2 : shapes[(y + 1) % 2]->points)
            {
                float dot = curNormal.DotProduct(pointC2);

                rangeC2.x = std::min(rangeC2.x, dot);
                rangeC2.y = std::max(rangeC2.y, dot);
            }

            if (rangeC1.y < rangeC2.x || rangeC2.y < rangeC1.x)
            {
                // Axis without overlapping so no collision
                return false;
            }
        }
    }

    return true;
}