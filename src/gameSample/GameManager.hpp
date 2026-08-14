#pragma once

#include "global/gameObject.hpp"
#include <functional>
#include "global/Event.hpp"

class UI;

enum GameState
{
    MENU,
    GAME,
    GAMEOVER
};

class GameManager : public GameObject
{
    static GameManager *m_instance;

    GameState m_state = GameState::MENU;
    int m_score = 0;
    Event<GameState, GameState> m_stateChangeCallbacks = {};

    UI *m_ui = nullptr;

public:
    GameManager(std::string name = "");
    ~GameManager();

    static GameManager *GetInstance();

    void Start() override;
    void Update() override;

    void SetState(GameState state);
    GameState GetState() const { return m_state; }

    void IncrementScore(int score);
    int GetScore() const { return m_score; }

    void Reset();

    int RegisterStateChange(std::function<void(GameState, GameState)> method);
    int UnregisterStateChange(size_t id);

    void SetUiReference(UI *ui) { m_ui = ui; }
};