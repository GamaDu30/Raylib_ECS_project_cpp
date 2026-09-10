#include "global/Scene.hpp"
#include "global/gameObject.hpp"
#include <algorithm>
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"
#include "components/Renderer/RenderComponent.hpp"
#include "components/Renderer/UI/CanvasComponent.hpp"
#include "components/Collider/ColliderComponent.hpp"
#include "global/Inputs.hpp"

unsigned int Scene::m_curUID = 0;
Scene *Scene::m_curScene = nullptr;

Scene::Scene(std::string name)
{
    if (name == "")
    {
        name = "Scene_" + std::to_string(m_curUID);
        m_curUID++;
    }

    m_name = name;
    m_gameObjects = {};
    m_gameObjectsToDestroy = {};
    m_camComp = nullptr;
    m_searchForCam = true;

    if (m_curScene == nullptr)
    {
        m_curScene = this;
    }
}

Scene::~Scene()
{
    for (GameObject *curGo : m_gameObjects)
    {
        delete curGo;
    }

    m_gameObjects.clear();

    if (m_curScene == this)
    {
        m_curScene = nullptr;
    }
}

void Scene::Start()
{
    for (GameObject *curGo : m_gameObjects)
    {
        curGo->Start();
    }
}

void Scene::Update()
{
    ColliderComponent::CheckCollisions();
    Inputs::Update();

    for (int i = m_gameObjects.size() - 1; i >= 0; i--)
    {
        if (m_gameObjects[i]->IsDestroyed())
        {
            m_gameObjectsToDestroy.push_back(m_gameObjects[i]);
            continue;
        }

        m_gameObjects[i]->Update();
    }

    for (int i = m_gameObjects.size() - 1; i >= 0; i--)
    {
        if (m_gameObjects[i]->IsDestroyed())
        {
            continue;
        }

        m_gameObjects[i]->LateUpdate();
    }

    for (int i = m_gameObjectsToDestroy.size() - 1; i >= 0; i--)
    {
        GameObject *goToDestroy = m_gameObjectsToDestroy[i];

        auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), goToDestroy);
        if (it != m_gameObjects.end())
        {
            m_gameObjects.erase(it);
        }

        delete goToDestroy;
    }

    m_gameObjectsToDestroy.clear();
}

void Scene::Render()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (m_camComp == nullptr && m_searchForCam)
    {
        SetCam();
    }

    CameraComponent::GetMainCam()->PushMatrix();

    // GameObject render
    std::vector<RenderComponent *> m_renderers = ComponentBase::GetInstancesAssignable<RenderComponent>();

    std::sort(m_renderers.begin(), m_renderers.end(),
              [](RenderComponent *a, RenderComponent *b)
              {
                  return a->GetOwner()->GetTransform()->GetPos().z < b->GetOwner()->GetTransform()->GetPos().z;
              });

    for (RenderComponent *renderComp : m_renderers)
    {
        renderComp->Render();
    }

    rlPopMatrix();

    // UI
    for (CanvasComponent *canvasComp : ComponentBase::GetInstancesOfType<CanvasComponent>())
    {
        canvasComp->Render();
    }

    if (DRAW_DEBUG)
    {
        for (ColliderComponent *colComp : ComponentBase::GetInstancesAssignable<ColliderComponent>())
        {
            colComp->DrawDebug();
        }

        for (RectTransformComponent *rectTransformComp : ComponentBase::GetInstancesAssignable<RectTransformComponent>())
        {
            rectTransformComp->DebugRender();
        }
    }

    EndDrawing();
}

void Scene::AddGameObject(GameObject *newGameObject)
{
    if (std::find(m_gameObjects.begin(), m_gameObjects.end(), newGameObject) != m_gameObjects.end())
    {
        TraceLog(LOG_ERROR, "Tried to add a gameobject in a scene when it's already present");
        return;
    }

    m_gameObjects.push_back(newGameObject);

    if (m_camComp == nullptr)
    {
        m_searchForCam = true;
    }
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
    auto it = std::find(m_gameObjects.begin(), m_gameObjects.end(), gameObject);
    if (it != m_gameObjects.end())
    {
        (*it)->Destroy();
    }
}

void Scene::SetCam()
{
    m_searchForCam = false;

    std::vector<CameraComponent *> camComp = ComponentBase::GetInstancesOfType<CameraComponent>();
    m_camComp = camComp.empty() ? nullptr : camComp[0];

    if (m_camComp == nullptr)
    {
        TraceLog(LOG_WARNING, "No Cam found for the scene");
    }
}

CameraComponent *Scene::GetMainCam()
{
    return m_camComp;
}

Scene *Scene::GetScene()
{
    return m_curScene;
}

GameObject *Scene::FindGameObject(std::string name)
{
    for (GameObject *curGo : m_gameObjects)
    {
        if (curGo->GetName() == name)
        {
            return curGo;
        }
    }

    return nullptr;
}
