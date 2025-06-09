#include "global/definitions.hpp"
#include "components/Renderer/RenderComponent.hpp"

class CircleRenderer : public RenderComponent
{
    raylib::Vector2 m_pos;
    float m_radius;
    raylib::Color m_color;
    bool m_isFilled;

public:
    CircleRenderer(raylib::Vector2 pos, float radius, raylib::Color color = WHITE, Anchor anchor = Anchor::Center, bool isFilled = true)
        : RenderComponent(anchor), m_pos(pos), m_radius(radius), m_color(color), m_isFilled(isFilled) {}

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();

    raylib::Vector2 &GetPos();
};