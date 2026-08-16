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

void GameManager::OnUpdate()
{
}

void GameManager::SetState(GameState state)
{
    if (m_state == state)
    {
        return;
    }

    const GameState previousState = m_state;
    m_stateChangeCallbacks.Invoke(previousState, state);

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

int GameManager::RegisterStateChange(std::function<void(GameState, GameState)> method)
{
    return m_stateChangeCallbacks.Add(method);
}

int GameManager::UnregisterStateChange(size_t id)
{
    return m_stateChangeCallbacks.Remove(id);
}
