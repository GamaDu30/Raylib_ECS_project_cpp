#include "global/definitions.hpp"
#include "components/ComponentBase.hpp"

ComponentBase::ComponentBase()
{
    m_isDirty = false;
    m_isActive = true;
}

ComponentBase::~ComponentBase()
{
}

void ComponentBase::Init(GameObject *owner)
{
    m_owner = owner;
}

void ComponentBase::Update()
{
    if (m_isActive)
    {
        OnUpdate();
    }
}

void ComponentBase::Destroy()
{
}

GameObject *ComponentBase::GetOwner()
{
    return m_owner;
}

void ComponentBase::SetActive(bool active)
{
    m_isActive = active;
}
