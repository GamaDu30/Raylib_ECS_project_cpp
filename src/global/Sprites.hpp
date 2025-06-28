#pragma once

#include "global/definitions.hpp"
#include <unordered_map>

class SpriteRenderer;
class RenderComponent;

struct Sprite
{
    Sprite() {};

    std::vector<SpriteRenderer *> renderers;

public:
    raylib::Texture2D texture;
};

class Sprites
{
    static std::unordered_map<std::string, Sprite *> m_sprites;

public:
    static raylib::Texture2D *GetSprite(SpriteRenderer *instance, std::string name);

    static void LoadSprite(SpriteRenderer *instance, std::string name);
    static void OnRendererDeleted(RenderComponent *renderer);
};