#include "Sprites.hpp"
#include <algorithm>
#include "components/Renderer/RenderComponent.hpp"
#include "components/Renderer/UI/UIRenderComponent.hpp"

std::unordered_map<std::string, Sprite *> Sprites::m_sprites = {};

raylib::Texture2D *Sprites::GetSprite(ComponentBase *instance, std::string name)
{
    if (!IsRenderer(instance) && !DEBUG_ACCESS)
    {
        TraceLog(LOG_WARNING, "Sprites: The component is not a renderer");
        return nullptr;
    }

    if (m_sprites.find(name) != m_sprites.end())
    {
        std::vector<ComponentBase *> &renderers = m_sprites[name]->renderers;

        if (std::find(renderers.begin(), renderers.end(), instance) == renderers.end())
        {
            renderers.push_back(instance);
        }

        return &m_sprites[name]->texture;
    }

    LoadSprite(instance, name);
    return &m_sprites[name]->texture;
}

void Sprites::OnRendererDeleted(ComponentBase *renderer)
{
    if (!IsRenderer(renderer) && !DEBUG_ACCESS)
    {
        TraceLog(LOG_WARNING, "Sprites: The component is not a renderer");
        return;
    }

    std::vector<std::string> spritesToDelete = {};
    std::vector<ComponentBase *> renderers;

    for (auto it = m_sprites.begin(); it != m_sprites.end(); it++)
    {
        auto &curRenderers = it->second->renderers;
        auto oldSize = it->second->renderers.size();

        curRenderers.erase(std::remove(curRenderers.begin(), curRenderers.end(), renderer), curRenderers.end());

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

void Sprites::LoadSprite(ComponentBase *instance, std::string name)
{
    if (!IsRenderer(instance) && !DEBUG_ACCESS)
    {
        TraceLog(LOG_WARNING, "Sprites: The component is not a renderer");
        return;
    }

    Sprite *newSprite = new Sprite();
    newSprite->texture = LoadTexture(name.c_str());
    newSprite->renderers = {instance};

    m_sprites[name] = newSprite;
}

bool Sprites::IsRenderer(ComponentBase *instance)
{
    if (dynamic_cast<RenderComponent *>(instance) != nullptr || (dynamic_cast<UIRenderComponent *>(instance) != nullptr))
    {
        return true;
    }

    return false;
}