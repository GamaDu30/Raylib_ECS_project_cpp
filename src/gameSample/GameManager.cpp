#include "gameSample/GameManager.hpp"
#include "gameSample/UI.hpp"
#include "GameManager.hpp"

GameManager *GameManager::m_instance = nullptr;

GameManager::GameManager(std::string name) : GameObject(name)
{
    if (m_instance == nullptr)
    {
        m_instance = this;
    }
}

GameManager::~GameManager()
{
    if (m_instance == this)
    {
        m_instance = nullptr;
    }
}

GameManager *GameManager::GetInstance()
{
    if (m_instance == nullptr)
    {
        m_instance = new GameManager("GameManager");
    }

    return m_instance;
}

void GameManager::Start()
{
    GameObject::Start();
}

void GameManager::Update()
{
    GameObject::Update();
}

void GameManager::SetState(GameState state)
{
    if (m_state == state)
    {
        return;
    }

    for (auto &callback : m_stateChangeCallbacks)
    {
        callback.method(m_state, state);
    }

    m_state = state;
}

void GameManager::IncrementScore(int score)
{
    m_score += score;

    if (m_ui)
    {
        m_ui->OnScoreChange(m_score);
    }
}

void GameManager::Reset()
{
    m_score = 0;
    m_ui->OnScoreChange(m_score);
    SetState(GameState::MENU);
}

void GameManager::RegisterStateChange(void *owner, std::function<void(GameState, GameState)> method)
{
    m_stateChangeCallbacks.push_back({owner, std::move(method)});
}

void GameManager::UnregisterStateChange(void *owner)
{
    m_stateChangeCallbacks.erase(std::remove_if(m_stateChangeCallbacks.begin(), m_stateChangeCallbacks.end(),
                                                [owner](const GameStateCallback &callback)
                                                { return callback.owner == owner; }),
                                 m_stateChangeCallbacks.end());
}
