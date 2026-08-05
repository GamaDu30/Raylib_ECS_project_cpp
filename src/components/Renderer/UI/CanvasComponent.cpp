#include "CanvasComponent.hpp"
#include "global/gameObject.hpp"
#include "algorithm"
#include "components/RectTransformComponent.hpp"
#include "components/Renderer/UI/UIRenderComponent.hpp"

CanvasComponent::CanvasComponent()
{
}

CanvasComponent::~CanvasComponent()
{
}

void CanvasComponent::Init(GameObject *owner)
{
    Component::Init(owner);
    m_owner->AddComponentInternal<RectTransformComponent>();
}

void CanvasComponent::OnUpdate()
{
}

void CanvasComponent::Destroy()
{
}

void CanvasComponent::Render()
{
    std::vector<GameObject *> gameObjectsToRender = {m_owner};
    GameObject *curGameobject;

    while (gameObjectsToRender.size() > 0)
    {
        curGameobject = gameObjectsToRender[0];

        // Get all children of curGameobject
        for (TransformComponent *child : curGameobject->GetTransform()->GetChildren())
        {
            gameObjectsToRender.push_back(child->GetOwner());
        }

        if (curGameobject->GetComponent<CanvasComponent>())
        {
            gameObjectsToRender.erase(std::remove(gameObjectsToRender.begin(), gameObjectsToRender.end(), curGameobject), gameObjectsToRender.end());
            continue;
        }

        std::vector<UIRenderComponent *> uiRenderComps = curGameobject->GetComponents<UIRenderComponent>();
        for (UIRenderComponent *uiRenderComp : uiRenderComps)
        {
            if (uiRenderComp)
            {
                uiRenderComp->Render();
            }
        }

        // Remove curGameobject from gameObjectsToRender
        gameObjectsToRender.erase(std::remove(gameObjectsToRender.begin(), gameObjectsToRender.end(), curGameobject), gameObjectsToRender.end());
    }
}

ViewMode CanvasComponent::GetViewMode()
{
    return m_viewMode;
}

raylib::Rectangle CanvasComponent::GetBorder()
{
    raylib::Rectangle border = raylib::Rectangle(0, 0, GetScreenWidth(), GetScreenHeight());

    if (m_viewMode == ViewMode::WorldSpace)
    {
        raylib::Vector3 transformPos = m_owner->GetComponent<RectTransformComponent>()->GetPos();
        border.SetPosition(border.GetPosition() + raylib::Vector2(transformPos.x, transformPos.y));
    }

    return border;
}
