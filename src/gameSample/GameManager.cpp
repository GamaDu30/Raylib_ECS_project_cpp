#include "gameSample/GameManager.hpp"
#include "GameManager.hpp"

GameManager *GameManager::s_instance = new GameManager("GameManager");

GameManager::GameManager(std::string name) : GameObject(name)
{
    if (s_instance == nullptr)
    {
        s_instance = this;
    }
}

GameManager::~GameManager()
{
    if (s_instance == this)
    {
        s_instance = nullptr;
    }
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
    if (m_state != state)
    {
        for (auto &callback : m_stateChangeCallbacks)
        {
            callback.method(m_state, state);
        }

        m_state = state;
    }
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
