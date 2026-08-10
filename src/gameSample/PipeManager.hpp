#pragma once
#include "global/definitions.hpp"
#include "global/gameObject.hpp"
#include "gameSample/GameManager.hpp"

struct PipeInstance
{
    GameObject *pipeGo;
    float lastX;
};

class PipeManager : public GameObject
{
    std::vector<PipeInstance *> m_pipes = std::vector<PipeInstance *>();

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

    void OnGameStateChange(GameState oldState, GameState newState);
};