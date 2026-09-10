#pragma once

#include "global/definitions.hpp"
#include <unordered_map>
#include "components/Renderer/RenderComponentBase.hpp"

class ComponentBase;

struct Sprite
{
    Sprite() {};

    std::vector<ComponentBase *> renderers;

public:
    raylib::Texture2D texture;
};

class Sprites
{
    static std::unordered_map<std::string, Sprite *> m_sprites;

public:
    static raylib::Texture2D *GetSprite(RenderComponentBase *instance, std::string name);

    static void LoadSprite(RenderComponentBase *instance, std::string name);
    static void OnRendererDeleted(RenderComponentBase *renderer);

    static bool IsRenderer(RenderComponentBase *instance);
};