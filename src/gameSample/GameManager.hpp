#pragma once

#include "global/gameObject.hpp"
#include <functional>

enum GameState
{
    MENU,
    GAME,
    GAMEOVER
};

struct GameStateCallback
{
    void *owner;
    std::function<void(GameState, GameState)> method;
};

class GameManager : public GameObject
{
    static GameManager *s_instance;

    GameState m_state = GameState::MENU;
    int m_score = 0;
    std::vector<GameStateCallback> m_stateChangeCallbacks = {};

public:
    GameManager(std::string name = "");
    ~GameManager();

    static GameManager *GetInstance() { return s_instance; }

    void Start() override;
    void Update() override;

    void SetState(GameState state);
    GameState GetState() const { return m_state; }

    void IncrementScore(int score) { m_score += score; }
    int GetScore() const { return m_score; }

    void RegisterStateChange(void *owner, std::function<void(GameState, GameState)> method);
    void UnregisterStateChange(void *owner);
};

// TODO: Implement event for state change