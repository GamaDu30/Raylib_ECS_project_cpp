#pragma once

#include "global/definitions.hpp"
#include "global/gameObject.hpp"
#include "gameSample/GameManager.hpp"

class TextComponent;

class UI : public GameObject
{
    GameObject *m_playButton = nullptr;
    GameObject *m_mainMenuButton = nullptr;
    GameObject *m_scoreText = nullptr;

public:
    UI(std::string name = "") : GameObject(name) {}
    ~UI() {}

    void Start() override;

    void OnGameStateChange(GameState oldState, GameState newState);

    void OnScoreChange(int newScore);

protected:
    void OnUpdate() override;
};