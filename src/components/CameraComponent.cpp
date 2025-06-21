#include "components/CameraComponent.hpp"
#include "global/gameObject.hpp"
#include "components/TransformComponent.hpp"

CameraComponent *CameraComponent::m_mainCam = nullptr;

CameraComponent::CameraComponent(Color bgColor)
{
    m_zoom = 1;
    m_rotation = 0.f;

    m_bgColor = bgColor;

    if (m_mainCam == nullptr)
    {
        m_mainCam = this;
    }
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::UpdateMatrix()
{
    raylib::Vector3 ownerPos = m_owner->GetTransform()->GetPos();
    m_matrix = MatrixMultiply(MatrixMultiply(
                                  MatrixScale(m_zoom, m_zoom, 1), MatrixRotateZ(m_rotation)),
                              MatrixTranslate(-ownerPos.x + SCREEN_W * 0.5f, -ownerPos.y + SCREEN_H * 0.5f, 0));
}

void CameraComponent::Init(GameObject *owner)
{
    Component::Init(owner);
    UpdateMatrix();
}

void CameraComponent::Update()
{
    Component::Update();

    raylib::Vector3 ownerPos = m_owner->GetTransform()->GetPos();

    if (m_lastPos != ownerPos || m_lastZoom != m_zoom || m_lastRotation != m_rotation)
    {
        m_lastPos = ownerPos;
        m_lastZoom = m_zoom;
        m_lastRotation = m_rotation;

        m_isDirty = true;
    }

    if (m_isDirty)
    {
        UpdateMatrix();

        m_isDirty = false;
    }
}

void CameraComponent::Destroy()
{
    Component::Destroy();
}

void CameraComponent::PushMatrix()
{
    rlPushMatrix();
    rlMultMatrixf(m_matrix.ToFloatV().v);
    ClearBackground(m_bgColor);
}
raylib::Vector2 CameraComponent::GetMousePos()
{
    raylib::Vector2 mousePos = GetMousePosition();
    mousePos.x += m_owner->GetTransform()->GetPos().x - SCREEN_W * 0.5f;
    mousePos.y += m_owner->GetTransform()->GetPos().y - SCREEN_H * 0.5f;
    return mousePos;
}

CameraComponent *CameraComponent::GetMainCam()
{
    return m_mainCam;
}