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

public:
    Scene(std::string name = "");
    ~Scene();

    void Update();
    void Render();

    GameObject *CreateGameObject(std::string name = "");
    void AddGameObject(GameObject *newGameObject);
    void RemoveGameObject(GameObject *gameObject);

    void SetCam();
};