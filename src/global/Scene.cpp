#include "global/Scene.hpp"
#include "global/gameObject.hpp"
#include "Scene.hpp"
#include <algorithm>
#include "components/TransformComponent.hpp"
#include "components/CameraComponent.hpp"

unsigned int Scene::m_curUID = 0;

Scene::Scene(std::string name)
{
    if (name == "")
    {
        name = "Scene_" + std::to_string(m_curUID);
        m_curUID++;
    }

    m_name = name;
    m_gameObjects = {};
    m_camComp = nullptr;
    m_searchForCam = true;
}

Scene::~Scene()
{
}

void Scene::Update()
{
    for (GameObject *curGo : m_gameObjects)
    {
        curGo->Update();
    }
}

void Scene::Render()
{
    if (m_camComp == nullptr && m_searchForCam)
    {
        SetCam();
    }

    std::sort(m_gameObjects.begin(), m_gameObjects.end(),
              [](GameObject *a, GameObject *b)
              {
                  return a->GetTransform()->GetPos().z < b->GetTransform()->GetPos().z;
              });

    if (m_camComp != nullptr)
    {
        m_camComp->PushMatrix();
    }

    for (GameObject *curGo : m_gameObjects)
    {
        curGo->Render();
    }

    rlPopMatrix();
}

GameObject *Scene::CreateGameObject(std::string name)
{
    GameObject *newGo = new GameObject(name);
    AddGameObject(newGo);
    return newGo;
}

void Scene::AddGameObject(GameObject *newGameObject)
{
    if (std::find(m_gameObjects.begin(), m_gameObjects.end(), newGameObject) != m_gameObjects.end())
    {
        TraceLog(LOG_ERROR, "Tried to add a gameobject in a scene when it's already present");
        return;
    }

    m_gameObjects.push_back(newGameObject);

    m_searchForCam = true;
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
    m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), gameObject), m_gameObjects.end());
}

void Scene::SetCam()
{
    m_searchForCam = false;

    for (GameObject *curGo : m_gameObjects)
    {
        CameraComponent *camComp = curGo->GetComponent<CameraComponent>();

        if (camComp != nullptr)
        {
            m_camComp = camComp;
            return;
        }
    }

    TraceLog(LOG_ERROR, "No Cam found for the scene");
}

CameraComponent *Scene::GetMainCam()
{
    return m_camComp;
}
