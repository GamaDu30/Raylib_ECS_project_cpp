#include "definitions.hpp"
#include "components/RenderComponent.hpp"

class SpriteRenderer : public RenderComponent
{
    raylib::Texture2D m_texture;

    Anchor m_anchor;

public:
    SpriteRenderer(std::string fileName, Anchor anchor = Anchor::Center);

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();
};