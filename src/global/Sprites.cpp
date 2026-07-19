#include "Sprites.hpp"
#include <algorithm>
#include "components/Renderer/RenderComponent.hpp"
#include "components/Renderer/UI/UIRenderComponent.hpp"

std::unordered_map<std::string, Sprite *> Sprites::m_sprites = {};

raylib::Texture2D *Sprites::GetSprite(Component *instance, std::string name)
{
    if (!IsRenderer(instance))
    {
        TraceLog(LOG_WARNING, "Sprites: The component is not a renderer");
        return nullptr;
    }

    if (m_sprites.count(name))
    {
        if (std::find(m_sprites[name]->renderers.begin(), m_sprites[name]->renderers.end(), instance) == m_sprites[name]->renderers.end())
        {
            m_sprites[name]->renderers.push_back(instance);
        }

        return &m_sprites[name]->texture;
    }

    LoadSprite(instance, name);
    return &m_sprites[name]->texture;
}

void Sprites::OnRendererDeleted(Component *renderer)
{
    if (!IsRenderer(renderer))
    {
        TraceLog(LOG_WARNING, "Sprites: The component is not a renderer");
        return;
    }

    std::vector<std::string> spritesToDelete = {};

    for (auto &[spriteName, sprite] : m_sprites)
    {
        bool foundRenderer = false;
        for (int i = sprite->renderers.size() - 1; i >= 0; i--)
        {
            if (sprite->renderers[i] == renderer)
            {
                sprite->renderers.erase(std::remove(sprite->renderers.begin(), sprite->renderers.end(), sprite->renderers[i]), sprite->renderers.end());
                foundRenderer = true;
                break;
            }
        }

        if (sprite->renderers.size() == 0)
        {
            spritesToDelete.push_back(spriteName);
        }

        if (foundRenderer)
        {
            break;
        }
    }

    for (std::string spriteName : spritesToDelete)
    {
        delete m_sprites[spriteName];
        m_sprites.erase(spriteName);
    }
}

void Sprites::LoadSprite(Component *instance, std::string name)
{
    if (!IsRenderer(instance))
    {
        TraceLog(LOG_WARNING, "Sprites: The component is not a renderer");
        return;
    }

    Sprite *newSprite = new Sprite();
    newSprite->texture = LoadTexture(name.c_str());
    newSprite->renderers = {instance};

    m_sprites[name] = newSprite;
}

bool Sprites::IsRenderer(Component *instance)
{
    if (dynamic_cast<RenderComponent *>(instance) != nullptr || (dynamic_cast<UIRenderComponent *>(instance) != nullptr))
    {
        return true;
    }

    return false;
}