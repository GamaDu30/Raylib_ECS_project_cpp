#include "gameSample/Bird.hpp"
#include "components/TransformComponent.hpp"
#include "components/Renderer/SpriteRenderer.hpp"
#include "global/Inputs.hpp"
#include "components/Collider/CircleCollider.hpp"

void Bird::Start()
{
    GameObject::Start();

    m_velocityMax = 3.f;
    m_velocity = -m_velocityMax;
    m_gravity = 4.f;
    m_jumpForce = 2.f;
    targetRotation = 0.f;

    SpriteRenderer *sprite = AddComponent<SpriteRenderer>("bird.png");
    GetTransform()->GetScale() = raylib::Vector2(0.25f, 0.25f);
    AddComponent<CircleCollider>(sprite->GetTexture()->width * 0.5f * GetTransform()->GetScale().x);

    Inputs::RegisterInput(KEY_SPACE, KeyState::PRESSED, [this]
                          { m_velocity = -m_jumpForce; });
}

void Bird::Update()
{
    GameObject::Update();

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
        shouldExit = true;
    }
}