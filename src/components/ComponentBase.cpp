#include "global/definitions.hpp"
#include "components/ComponentBase.hpp"

ComponentBase::ComponentBase()
{
    m_isDirty = false;
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
}
void ComponentBase::Destroy()
{
}

GameObject *ComponentBase::GetOwner()
{
    return m_owner;
}
