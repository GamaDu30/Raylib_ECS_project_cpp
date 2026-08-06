#include "gameSample/Bird.hpp"
#include "components/TransformComponent.hpp"
#include "components/Renderer/SpriteRenderer.hpp"
#include "global/Inputs.hpp"
#include "components/Collider/CircleCollider.hpp"

Bird::Bird(std::string name) : GameObject(name)
{
}

Bird::~Bird()
{
    Inputs::UnregisterInput(KEY_SPACE, KeyState::PRESSED, this);
}

void Bird::Reset()
{
    m_velocityMax = 3.f;
    m_velocity = -m_velocityMax;
    m_gravity = 4.f;
    m_jumpForce = 2.5f;
    targetRotation = 0.f;

    GetTransform()->GetRotation() = 0.f;
    GetTransform()->GetPos() = raylib::Vector3(0.f, 0.f, 0.f);
}

void Bird::Start()
{
    GameObject::Start();

    Reset();

    SpriteRenderer *sprite = AddComponent<SpriteRenderer>("bird.png");
    GetTransform()->GetScale() = raylib::Vector2(0.25f, 0.25f);
    AddComponent<CircleCollider>(sprite->GetTexture()->width * 0.4f);

    Inputs::RegisterInput(KEY_SPACE, KeyState::PRESSED, this, [this]
                          { m_velocity = -m_jumpForce; });

    GameManager::GetInstance()->RegisterStateChange(this, [this](GameState oldState, GameState newState)
                                                    { OnGameStateChange(oldState, newState); });
}

void Bird::Update()
{
    GameObject::Update();

    if (GameManager::GetInstance()->GetState() != GameState::GAME)
    {
        return;
    }

    m_velocity += m_gravity * GetFrameTime();
    m_velocity = std::min(m_velocity, m_velocityMax);
    GetTransform()->GetPos().y += m_velocity;

    float velocityPercentage = (m_velocity + m_jumpForce) / (m_velocityMax + m_jumpForce);
    targetRotation = Lerp(-1.f, 1.f, velocityPercentage);

    GetTransform()->GetRotation() = Lerp(GetTransform()->GetRotation(), targetRotation, GetFrameTime() * 10.f);
}

void Bird::OnCollisionEnter(ColliderComponent *collider)
{
    GameObject::OnCollisionEnter(collider);

    if (collider->GetOwner()->GetName() == "Pipe")
    {
        GameManager::GetInstance()->SetState(GameState::GAMEOVER);
    }
}
void Bird::OnGameStateChange(GameState oldState, GameState newState)
{
    if (newState == GameState::MENU || newState == GameState::GAME)
    {
        Reset();
    }
}