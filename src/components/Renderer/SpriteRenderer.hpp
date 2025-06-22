#include "global/definitions.hpp"
#include "components/Renderer/RenderComponent.hpp"

class SpriteRenderer : public RenderComponent
{
    raylib::Texture2D m_texture;

public:
    SpriteRenderer(std::string fileName, Anchor anchor = Anchor::Center, raylib::Color color = WHITE, raylib::Vector2 offset = raylib::Vector2());

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    virtual void Render();

    raylib::Texture2D *GetTexture();
};