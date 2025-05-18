#include "components/TransformComponent.hpp"
#include "gameObject.hpp"
#include "algorithm"
#include "TransformComponent.hpp"

TransformComponent::TransformComponent()
{
}

void TransformComponent::Init(GameObject *owner)
{
    Component::Init(owner);
    UpdateLocalMatrix();
}

void TransformComponent::Update()
{
    Component::Update();

    // TODO: Change with getter/setter
    if (m_lastPos != m_pos || m_lastScale != m_scale || m_lastRotation != m_rotation)
    {
        m_lastPos = m_pos;
        m_lastScale = m_scale;
        m_lastRotation = m_rotation;

        m_isDirty = true;
    }

    if (m_isDirty)
    {
        UpdateLocalMatrix();

        m_isDirty = false;
    }
}

void TransformComponent::Destroy()
{
    Component::Destroy();
}

void TransformComponent::UpdateLocalMatrix()
{
    m_matrix = MatrixMultiply(MatrixMultiply(
                                  MatrixScale(m_scale.x, m_scale.y, 1), MatrixRotateZ(m_rotation)),
                              MatrixTranslate(m_pos.x, m_pos.y, m_pos.z));
}

raylib::Vector3 &TransformComponent::GetPos()
{
    return m_pos;
}

raylib::Vector2 &TransformComponent::GetScale()
{
    return m_scale;
}

float &TransformComponent::GetRotation()
{
    return m_rotation;
}

void TransformComponent::SetDirty()
{
    m_isDirty = true;
}

void TransformComponent::AddChild(TransformComponent *newChild)
{
    m_children.push_back(newChild);
    newChild->SetParent(this);
}

void TransformComponent::RemoveChild(TransformComponent *childToRemove)
{
    if (childToRemove == nullptr)
    {
        TraceLog(LOG_ERROR, "the child you tried to remove on transform \"%s\" is not valid", m_owner->GetName());
        return;
    }

    m_children.erase(std::remove(m_children.begin(), m_children.end(), childToRemove), m_children.end());

    if (childToRemove->m_parent == this)
    {
        childToRemove->m_parent = nullptr;
        childToRemove->m_isDirty = true;
    }
}

void TransformComponent::RemoveChild(int id)
{
    if (id >= m_children.size() || id < 0)
    {
        TraceLog(LOG_ERROR, "You tried to remove child n°%d but the gameObject \"%s\" only have %d children", id, m_owner->GetName(), m_children.size());
        return;
    }

    TransformComponent *removedChild = m_children.erase(m_children.begin() + id)[0];

    if (removedChild->m_parent == this)
    {
        removedChild->m_parent = nullptr;
        removedChild->m_isDirty = true;
    }
}

std::vector<TransformComponent *> TransformComponent::GetChildren()
{
    return m_children;
}

TransformComponent *TransformComponent::GetChild(int id)
{
    if (id < 0 || id >= m_children.size())
    {
        TraceLog(LOG_ERROR, "TransformComponent::GetChild id provided is out of bound: %d", id);
        return nullptr;
    }

    if (m_children.size() == 0)
    {
        return nullptr;
    }

    return m_children[id];
}

void TransformComponent::SetParent(TransformComponent *newParent)
{
    if (m_parent == newParent)
    {
        return;
    }

    if (m_parent != nullptr)
    {
        m_parent->RemoveChild(this);
    }

    m_parent = newParent;
    m_isDirty = true;
}

raylib::Matrix TransformComponent::GetMatrix()
{
    if (m_parent == nullptr)
    {
        return m_matrix;
    }

    return MatrixMultiply(m_matrix, m_parent->GetMatrix());
}

void TransformComponent::PushMatrix()
{
    rlPushMatrix();
    rlMultMatrixf(GetMatrix().ToFloatV().v);
}