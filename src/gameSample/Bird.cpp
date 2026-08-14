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
    Inputs::UnregisterInput(m_inputJumpId);
}

void Bird::Reset()
{
    m_velocityMax = 500.f;
    m_velocity = raylib::Vector2(0.f, -m_velocityMax);
    m_gravity = 800.f;
    m_jumpForce = 450.f;
    targetRotation = 0.f;
    m_state = BirdState::ALIVE;

    GetTransform()->GetRotation() = 0.f;
    GetTransform()->GetPos() = raylib::Vector3(0.f, 0.f, 1.f);
}

void Bird::Start()
{
    GameObject::Start();

    Reset();

    SpriteRenderer *sprite = AddComponent<SpriteRenderer>("bird.png");
    GetTransform()->GetScale() = raylib::Vector2(0.25f, 0.25f);
    AddComponent<CircleCollider>(sprite->GetTexture()->width * 0.4f);

    m_inputJumpId = Inputs::RegisterInput(KEY_SPACE, KeyState::PRESSED, [this]
                                          { Jump(); });

    GameManager::GetInstance()->RegisterStateChange([this](GameState oldState, GameState newState)
                                                    { OnGameStateChange(oldState, newState); });
}

void Bird::Update()
{
    GameObject::Update();

    if (GameManager::GetInstance()->GetState() == GameState::MENU)
    {
        return;
    }

    m_velocity.y += m_gravity * GetFrameTime();
    m_velocity.y = std::min(m_velocity.y, m_velocityMax);
    GetTransform()->GetPos() += raylib::Vector3(m_velocity.x, m_velocity.y, 0) * GetFrameTime();

    switch (m_state)
    {
    case BirdState::ALIVE:
    {
        float velocityPercentage = (m_velocity.y + m_jumpForce) / (m_velocityMax + m_jumpForce);
        targetRotation = Lerp(-1.f, 1.f, velocityPercentage);

        GetTransform()->GetRotation() = Lerp(GetTransform()->GetRotation(), targetRotation, GetFrameTime() * 10.f);
        break;
    }
    case BirdState::DEAD:
    {
        GetTransform()->GetRotation() += GetFrameTime() * 5.f;
    }
        return;
    default:
        break;
    }
}

void Bird::OnCollisionEnter(ColliderComponent *collider)
{
    GameObject::OnCollisionEnter(collider);

    if (m_state == BirdState::DEAD)
    {
        return;
    }

    if (collider->GetOwner()->GetName() == "Pipe")
    {
        GameManager::GetInstance()->SetState(GameState::GAMEOVER);

        m_state = BirdState::DEAD;
        m_velocity = raylib::Vector2(0.f, -300.f).Rotate(-PI * 0.25f + (PI * 0.5f * (GetRandomValue(0, INT_MAX) / static_cast<float>(INT_MAX))));
    }
}
void Bird::OnGameStateChange(GameState oldState, GameState newState)
{
    if (newState == GameState::MENU || newState == GameState::GAME)
    {
        Reset();
    }
}

void Bird::Jump()
{
    if (m_state == BirdState::DEAD)
    {
        return;
    }

    m_velocity.y = -m_jumpForce;
}