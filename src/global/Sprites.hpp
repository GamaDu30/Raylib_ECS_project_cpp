#pragma once

#include "global/definitions.hpp"
#include <unordered_map>
#include "components/Renderer/RenderComponentBase.hpp"

class ComponentBase;

struct Sprite
{
    Sprite() {};

    std::vector<unsigned int> renderers;

public:
    raylib::Texture2D texture;
};

class Sprites
{
    static std::unordered_map<std::string, Sprite *> m_sprites;

public:
    static raylib::Texture2D *GetSprite(unsigned int rendererUID, std::string name);

    static void LoadSprite(unsigned int instance, std::string name);
    static void OnRendererDeleted(unsigned int rendererUID);
};