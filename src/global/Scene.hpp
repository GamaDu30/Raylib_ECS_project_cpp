#pragma once

#include "global/definitions.hpp"

class GameObject;
class CameraComponent;

class Scene
{
    static unsigned int m_curUID;
    static Scene *m_curScene;

    std::string m_name;

    std::vector<GameObject *> m_gameObjects;

    CameraComponent *m_camComp;
    bool m_searchForCam;

public:
    Scene(std::string name = "");
    ~Scene();

    void Start();
    void Update();
    void Render();

    template <typename T = GameObject>
    T *CreateGameObject(std::string name = "");
    void AddGameObject(GameObject *newGameObject);
    void RemoveGameObject(GameObject *gameObject);

    void SetCam();

    CameraComponent *GetMainCam();
    static Scene *GetScene();

    GameObject *FindGameObject(std::string name);
};

template <typename T>
T *Scene::CreateGameObject(std::string name)
{
    static_assert(std::is_base_of_v<GameObject, T>, "(Scene::CreateGameObject) T must inherit from GameObject");

    T *newGo = new T(name);
    AddGameObject(newGo);

    newGo->Start();
    return newGo;
}