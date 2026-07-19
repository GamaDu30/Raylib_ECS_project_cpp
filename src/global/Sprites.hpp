#pragma once

#include "global/definitions.hpp"
#include <unordered_map>

class Component;

struct Sprite
{
    Sprite() {};

    std::vector<Component *> renderers;

public:
    raylib::Texture2D texture;
};

class Sprites
{
    static std::unordered_map<std::string, Sprite *> m_sprites;

public:
    static raylib::Texture2D *GetSprite(Component *instance, std::string name);

    static void LoadSprite(Component *instance, std::string name);
    static void OnRendererDeleted(Component *renderer);

    static bool IsRenderer(Component *instance);
};