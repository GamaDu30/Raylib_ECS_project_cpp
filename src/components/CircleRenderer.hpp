#include "definitions.hpp"
#include "components/RenderComponent.hpp"

class CircleRenderer : public RenderComponent
{
    raylib::Vector2 m_pos;
    float m_radius;
    raylib::Color m_color;
    bool m_isFilled;

public:
    CircleRenderer(raylib::Vector2 pos, float radius, raylib::Color color, bool isFilled = true)
        : m_pos(pos), m_radius(radius), m_color(color), m_isFilled(isFilled) {}

    virtual void Render();

    raylib::Vector2 &GetPos();
};