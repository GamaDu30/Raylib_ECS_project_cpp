#include "gameSample/UI.hpp"
#include "components/Renderer/UI/CanvasComponent.hpp"
#include "global/Scene.hpp"
#include "components/Renderer/UI/ButtonComponent.hpp"
#include "components/Renderer/UI/TextComponent.hpp"
#include "components/Renderer/UI/ImageComponent.hpp"

void UI::Start()
{
    GameObject::Start();

    GameManager::GetInstance()->RegisterStateChange(this, [this](GameState oldState, GameState newState)
                                                    { OnGameStateChange(oldState, newState); });

    AddComponent<CanvasComponent>();

    m_playButton = Scene::GetScene()->CreateGameObject("Button");
    m_playButton->GetTransform()->SetParent(this->GetTransform());
    m_playButton->GetComponent<RectTransformComponent>()->GetAnchorMin() = raylib::Vector2(0.4f, 0.65f);
    m_playButton->GetComponent<RectTransformComponent>()->GetAnchorMax() = raylib::Vector2(0.6f, 0.75f);

    ButtonComponent *playButtonComp = m_playButton->AddComponent<ButtonComponent>(
        ImageData{.textureName = "button.png"},
        TextData{.text = "Play", .fontSize = 30, .alignmentH = TextAlignmentH::CENTER, .alignmentV = TextAlignmentV::MIDDLE});
    playButtonComp->SetOnClickCallback([this]()
                                       { GameManager::GetInstance()->SetState(GameState::GAME);
                                this->m_playButton->SetActive(false); });

    // Return to menu button
    m_mainMenuButton = Scene::GetScene()->CreateGameObject("Button");
    m_mainMenuButton->GetTransform()->SetParent(this->GetTransform());
    m_mainMenuButton->GetComponent<RectTransformComponent>()->GetAnchorMin() = raylib::Vector2(0.4f, 0.65f);
    m_mainMenuButton->GetComponent<RectTransformComponent>()->GetAnchorMax() = raylib::Vector2(0.6f, 0.75f);

    ButtonComponent *mainMenuButtonComp = m_mainMenuButton->AddComponent<ButtonComponent>(
        ImageData{.textureName = "button.png"},
        TextData{.text = "Exit", .fontSize = 30, .alignmentH = TextAlignmentH::CENTER, .alignmentV = TextAlignmentV::MIDDLE});
    mainMenuButtonComp->SetOnClickCallback([this]()
                                           { GameManager::GetInstance()->SetState(GameState::MENU);
                                this->m_mainMenuButton->SetActive(false); });
    m_mainMenuButton->SetActive(false);
}

void UI::Update()
{
    GameObject::Update();
}

void UI::OnGameStateChange(GameState oldState, GameState newState)
{
    if (newState == GameState::MENU)
    {
        this->m_playButton->SetActive(true);
    }
    else if (newState == GameState::GAMEOVER)
    {
        this->m_mainMenuButton->SetActive(true);
    }
}