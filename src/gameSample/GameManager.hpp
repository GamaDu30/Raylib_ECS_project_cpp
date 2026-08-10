#pragma once

#include "global/gameObject.hpp"
#include <functional>

class UI;

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

    UI *m_ui = nullptr;

public:
    GameManager(std::string name = "");
    ~GameManager();

    static GameManager *GetInstance() { return s_instance; }

    void Start() override;
    void Update() override;

    void SetState(GameState state);
    GameState GetState() const { return m_state; }

    void IncrementScore(int score);
    int GetScore() const { return m_score; }

    void Reset();

    void RegisterStateChange(void *owner, std::function<void(GameState, GameState)> method);
    void UnregisterStateChange(void *owner);

    void SetUiReference(UI *ui) { m_ui = ui; }
};