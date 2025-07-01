#pragma once
#include "global/definitions.hpp"
#include "global/gameObject.hpp"

class PipeManager : public GameObject
{
    std::vector<GameObject *> m_pipes = std::vector<GameObject *>();

    float m_timer;
    float m_cooldown;

    float m_pipeSpeed;
    float m_limit;

public:
    PipeManager(std::string name = "") : GameObject(name)
    {
    }
    ~PipeManager() {}

    void Start() override;
    void Update() override;
};