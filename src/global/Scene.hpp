#pragma once

#include "global/definitions.hpp"

class GameObject;

class Scene
{
    static unsigned int m_curUID;

    std::string m_name;

    std::vector<GameObject *> m_gameObjects;

public:
    Scene(std::string name);
    ~Scene();

    void Update();
    void Render();

    void AddGameObject(GameObject *newGameObject);
    void RemoveGameObject(GameObject *gameObject);
};