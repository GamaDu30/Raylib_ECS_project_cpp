#include "global/Scene.hpp"
#include "global/gameObject.hpp"
#include "Scene.hpp"
#include <algorithm>

unsigned int Scene::m_curUID = 0;

Scene::Scene(std::string name = "")
{
    if (name == "")
    {
        name = "Scene" + std::to_string(m_curUID);
        m_curUID++;
    }

    m_name = name;
    m_gameObjects = {};
}

Scene::~Scene()
{
}

void Scene::Update()
{
    GameObject::UpdateAll();
}

void Scene::Render()
{
    GameObject::RenderAll();
}

void Scene::AddGameObject(GameObject *newGameObject)
{
    if (std::find(m_gameObjects.begin(), m_gameObjects.end(), newGameObject) != m_gameObjects.end())
    {
        TraceLog(LOG_ERROR, "Tried to add a gameobject in a scene when it's already present");
        return;
    }

    m_gameObjects.push_back(newGameObject);
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
    m_gameObjects.erase(std::remove(m_gameObjects.begin(), m_gameObjects.end(), gameObject), m_gameObjects.end());
}
