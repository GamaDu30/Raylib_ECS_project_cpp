#include "RenderComponentBase.hpp"
#include "global/gameObject.hpp"

RenderComponentBase::RenderComponentBase()
{
}

RenderComponentBase::~RenderComponentBase()
{
}

void RenderComponentBase::Init(GameObject *owner)
{
    Component::Init(owner);
}

void RenderComponentBase::OnUpdate()
{
}

void RenderComponentBase::Destroy()
{
}

void RenderComponentBase::Render()
{
    if (!m_isActive)
    {
        return;
    }

    OnRender();
}

void RenderComponentBase::SetColor(raylib::Color color)
{
    m_color = color;
}