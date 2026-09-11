#include "Sprites.hpp"
#include <algorithm>
#include "components/Renderer/RenderComponent.hpp"
#include "components/Renderer/UI/UIRenderComponent.hpp"

std::unordered_map<std::string, Sprite *> Sprites::m_sprites = {};

raylib::Texture2D *Sprites::GetSprite(unsigned int rendererUID, std::string name)
{
    if (m_sprites.find(name) != m_sprites.end())
    {
        std::vector<unsigned int> &renderers = m_sprites[name]->renderers;

        if (std::find(renderers.begin(), renderers.end(), rendererUID) == renderers.end())
        {
            renderers.push_back(rendererUID);
            TraceLog(LOG_DEBUG, (name + " size: " + std::to_string(renderers.size())).c_str());
        }

        return &m_sprites[name]->texture;
    }

    LoadSprite(rendererUID, name);
    return &m_sprites[name]->texture;
}

void Sprites::OnRendererDeleted(unsigned int rendererUID)
{
    std::vector<std::string> spritesToDelete = {};
    std::vector<ComponentBase *> renderers;

    for (auto it = m_sprites.begin(); it != m_sprites.end(); it++)
    {
        auto &curRenderers = it->second->renderers;
        auto oldSize = it->second->renderers.size();

        curRenderers.erase(std::remove(curRenderers.begin(), curRenderers.end(), rendererUID), curRenderers.end());

        if (curRenderers.size() != oldSize)
        {
            if (curRenderers.empty())
            {
                m_sprites[it->first]->texture.Unload();
                delete m_sprites[it->first];
                m_sprites.erase(it);
            }

            break;
        }
    }
}

void Sprites::LoadSprite(unsigned int instance, std::string name)
{
    Sprite *newSprite = new Sprite();
    newSprite->texture = LoadTexture(name.c_str());
    newSprite->renderers = {instance};

    m_sprites[name] = newSprite;
}