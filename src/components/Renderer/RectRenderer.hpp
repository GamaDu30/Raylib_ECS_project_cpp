#include "global/definitions.hpp"
#include "components/Renderer/RenderComponent.hpp"

class RectRenderer : public RenderComponent
{
    raylib::Rectangle m_rect;
    bool m_filled;

public:
    RectRenderer(raylib::Vector2 size, raylib::Vector2 offset = raylib::Vector2(), Anchor anchor = Anchor::Center, Color color = WHITE, bool filled = true);

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();
};