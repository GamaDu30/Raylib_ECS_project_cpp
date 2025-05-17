#include "definitions.hpp"
#include "components/RenderComponent.hpp"

class CircleRenderer : public RenderComponent
{
    bool filled;
    raylib::Vector2 center;
    float radius;
    raylib::Color color;

public:
    CircleRenderer(Vector2 c, float r, Color col, bool fill = true)
        : center(c), radius(r), color(col), filled(fill) {}

    virtual void Render() override
    {
        if (filled)
            DrawCircleV(center, radius, color);
        else
            DrawCircleLines((int)center.x, (int)center.y, radius, color);
    }
};