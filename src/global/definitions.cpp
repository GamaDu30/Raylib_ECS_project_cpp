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

bool ColPolyPoly(PolyColInfo *p1, PolyColInfo *p2)
{
    raylib::Vector2 rangeC1, rangeC2;
    std::array<PolyColInfo *, 2> shapes = {p1, p2};

    for (int y = 0; y < shapes.size(); y++)
    {
        for (int i = 0; i < shapes[y]->points.size(); i++)
        {
            rangeC1 = raylib::Vector2(__FLT_MAX__, -__FLT_MAX__);
            rangeC2 = rangeC1;

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

bool ColPolyCircle(PolyColInfo *p, CircleColInfo *c)
{
    raylib::Vector2 rangeP, rangeC;

    if (IsKeyDown(KEY_SPACE))
    {
        int a = 0;
    }

    for (int i = 0; i < p->points.size(); i++)
    {
        rangeP = raylib::Vector2(__FLT_MAX__, -__FLT_MAX__);
        rangeC = rangeP;

        raylib::Vector2 curVec = (p->points[(i + 1) % p->points.size()] - p->points[i]).Normalize();
        raylib::Vector2 curNormal = raylib::Vector2(-curVec.y, curVec.x);

        for (raylib::Vector2 point : p->points)
        {
            float dot = curNormal.DotProduct(point);

            rangeP.x = std::min(rangeP.x, dot);
            rangeP.y = std::max(rangeP.y, dot);
        }

        float dot = curNormal.DotProduct(c->pos);

        rangeC.x = dot - c->radius;
        rangeC.y = dot + c->radius;

        if (rangeP.y < rangeC.x || rangeC.y < rangeP.x)
        {
            // Axis without overlapping so no collision
            return false;
        }
    }

    return true;
}

bool shouldExit = false;