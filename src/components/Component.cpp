#include "definitions.hpp"
#include "components/Component.hpp"

Component::Component()
{
    // TraceLog(LOG_DEBUG, "Component Constructor");
}

Component::~Component()
{
    // TraceLog(LOG_DEBUG, "Component Destructor");
}

void Component::Init(GameObject *owner)
{
    // TraceLog(LOG_DEBUG, "Component Init");
    m_owner = owner;
}
void Component::Update()
{
    // TraceLog(LOG_DEBUG, "Component Update");
}
void Component::Destroy()
{
    // TraceLog(LOG_DEBUG, "Component Destroyed");
}

GameObject *Component::GetOwner()
{
    return m_owner;
}
