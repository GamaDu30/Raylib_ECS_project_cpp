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

    if (m_lastPos != m_pos)
    {
        m_lastPos = m_pos;
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
    m_matrix = MatrixMultiply(
        MatrixTranslate(m_pos.x, m_pos.y, 0),
        MatrixMultiply(
            MatrixRotateZ(m_rotation),
            MatrixScale(m_scale.x, m_scale.y, 1)));
}

raylib::Vector2 &TransformComponent::GetPos()
{
    return m_pos;
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