#include "global/definitions.hpp"
#include "components/Renderer/RenderComponent.hpp"

class RectRenderer : public RenderComponent
{
    raylib::Rectangle m_rect;
    bool m_filled;
    Color m_color;

public:
    RectRenderer(const raylib::Rectangle &rect, Color color, bool filled = true);

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();
};