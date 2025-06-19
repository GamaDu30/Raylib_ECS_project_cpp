#pragma once

#include "global/definitions.hpp"

class GameObject;
class CameraComponent;

class Scene
{
    static unsigned int m_curUID;

    std::string m_name;

    std::vector<GameObject *> m_gameObjects;

    CameraComponent *m_camComp;
    bool m_searchForCam;

public:
    Scene(std::string name = "");
    ~Scene();

    void Update();
    void Render();

    template <typename T = GameObject>
    T *CreateGameObject(std::string name = "");
    void AddGameObject(GameObject *newGameObject);
    void RemoveGameObject(GameObject *gameObject);

    void SetCam();

    CameraComponent *GetMainCam();
};

template <typename T>
T *Scene::CreateGameObject(std::string name)
{
    static_assert(std::is_base_of_v<GameObject, T>, "(Scene::CreateGameObject) T must inherit from GameObject");

    T *newGo = new T(name);
    AddGameObject(newGo);
    return newGo;
}