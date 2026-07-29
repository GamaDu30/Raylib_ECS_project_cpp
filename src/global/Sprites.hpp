#pragma once

#include "global/definitions.hpp"
#include <unordered_map>

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
    static raylib::Texture2D *GetSprite(ComponentBase *instance, std::string name);

    static void LoadSprite(ComponentBase *instance, std::string name);
    static void OnRendererDeleted(ComponentBase *renderer);

    static bool IsRenderer(ComponentBase *instance);
};