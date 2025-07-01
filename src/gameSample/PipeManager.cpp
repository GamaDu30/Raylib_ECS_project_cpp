#include "gameSample/PipeManager.hpp"
#include "global/Scene.hpp"
#include "components/Renderer/SpriteRenderer.hpp"
#include "components/TransformComponent.hpp"
#include "algorithm"
#include "components/Collider/RectCollider.hpp"

void PipeManager::Start()
{
    GameObject::Start();

    m_timer = 0.f;
    m_cooldown = 2.f;

    m_pipeSpeed = 200.f;
    m_limit = -SCREEN_W * 0.6f;
}

void PipeManager::Update()
{
    GameObject::Update();

    for (int i = m_pipes.size() - 1; i >= 0; i--)
    {
        m_pipes[i]->GetTransform()->GetPos().x -= m_pipeSpeed * GetFrameTime();

        if (m_pipes[i]->GetTransform()->GetPos().x < m_limit)
        {
            Scene::GetScene()->RemoveGameObject(m_pipes[i]);
            m_pipes.erase(std::remove(m_pipes.begin(), m_pipes.end(), m_pipes[i]), m_pipes.end());
        }
    }

    if (m_timer > 0.f)
    {
        m_timer -= GetFrameTime();
        return;
    }

    m_timer = m_cooldown;

    float offset = GetRandomValue(-150, 150);

    GameObject *newPipe = Scene::GetScene()->CreateGameObject("Pipe");
    raylib::Texture2D *text = newPipe->AddComponent<SpriteRenderer>("pipe.png")->GetTexture();
    newPipe->GetTransform()->GetScale() *= 4.f;
    newPipe->AddComponent<RectCollider>(text->GetSize());
    newPipe->GetTransform()->GetPos().x = SCREEN_W * 0.6f;
    newPipe->GetTransform()->GetPos().y = offset + 300;
    m_pipes.push_back(newPipe);

    newPipe = Scene::GetScene()->CreateGameObject("Pipe");
    newPipe->AddComponent<SpriteRenderer>("pipe.png");
    newPipe->GetTransform()->GetScale() *= 4.f;
    newPipe->AddComponent<RectCollider>(text->GetSize());
    newPipe->GetTransform()->GetPos().x = SCREEN_W * 0.6f;
    newPipe->GetTransform()->GetPos().y = offset - 300;
    newPipe->GetTransform()->GetRotation() = 3.141;
    m_pipes.push_back(newPipe);
}