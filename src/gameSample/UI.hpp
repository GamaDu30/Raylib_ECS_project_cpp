#include "global/definitions.hpp"
#include "global/gameObject.hpp"
#include "gameSample/GameManager.hpp"

class UI : public GameObject
{
    GameObject *m_playButton = nullptr;
    GameObject *m_mainMenuButton = nullptr;

public:
    UI(std::string name = "") : GameObject(name) {}
    ~UI() {}

    void Start() override;
    void Update() override;

    void OnGameStateChange(GameState oldState, GameState newState);
};