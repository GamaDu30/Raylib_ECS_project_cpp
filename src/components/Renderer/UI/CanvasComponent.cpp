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

void CanvasComponent::Update()
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

        if (m_owner->GetComponent<CanvasComponent>())
        {
            gameObjectsToRender.erase(std::remove(gameObjectsToRender.begin(), gameObjectsToRender.end(), curGameobject), gameObjectsToRender.end());
            continue;
        }

        // Render curGameobject
        // curGameobject->GetComponent<UIRenderComponent>()->Render(this);

        // DEBUG
        RectTransformComponent *parentTransform = dynamic_cast<RectTransformComponent *>(curGameobject->GetTransform()->GetParent());
        curGameobject->GetComponent<RectTransformComponent>()->DebugRender();

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
    raylib::Rectangle border = raylib::Rectangle(0, 0, SCREEN_W, SCREEN_H);

    if (m_viewMode == ViewMode::WorldSpace)
    {
        // TODO: replace with RectTransformComponent.offset
        raylib::Vector3 transformPos = m_owner->GetComponent<RectTransformComponent>()->GetPos();
        border.SetPosition(border.GetPosition() + raylib::Vector2(transformPos.x, transformPos.y));
    }

    return border;
}
