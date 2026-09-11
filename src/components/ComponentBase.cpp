#include "global/definitions.hpp"
#include "components/ComponentBase.hpp"

unsigned int ComponentBase::m_curUID = 0;

std::unordered_map<std::type_index, std::vector<ComponentBase *>> &ComponentBase::GetRegistry()
{
    // Heap allocation intentionally avoids static deinit order issues at shutdown.
    static auto *registry = new std::unordered_map<std::type_index, std::vector<ComponentBase *>>();
    return *registry;
}

ComponentBase::ComponentBase()
    : m_registeredConcreteType(typeid(ComponentBase))
{
    m_owner = nullptr;
    m_isDirty = false;
    m_isActive = true;
    m_isRegistered = false;
    m_uid = m_curUID++;
}

ComponentBase::~ComponentBase()
{
    UnregisterConcreteInstance();
}

void ComponentBase::Init(GameObject *owner)
{
    m_owner = owner;
    RegisterConcreteInstance();
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
    UnregisterConcreteInstance();
}

GameObject *ComponentBase::GetOwner()
{
    return m_owner;
}

void ComponentBase::SetActive(bool active)
{
    m_isActive = active;
}

unsigned int ComponentBase::GetUID()
{
    return m_uid;
}

void ComponentBase::RegisterConcreteInstance()
{
    if (m_isRegistered)
    {
        return;
    }

    std::type_index concreteType = std::type_index(typeid(*this));
    auto &registry = GetRegistry();
    std::vector<ComponentBase *> &instances = registry[concreteType];

    if (std::find(instances.begin(), instances.end(), this) == instances.end())
    {
        instances.push_back(this);
        m_registeredConcreteType = concreteType;
        m_isRegistered = true;
    }
}

void ComponentBase::UnregisterConcreteInstance()
{
    if (!m_isRegistered)
    {
        return;
    }

    auto &registry = GetRegistry();
    auto mapIt = registry.find(m_registeredConcreteType);

    if (mapIt == registry.end())
    {
        m_isRegistered = false;
        return;
    }

    std::vector<ComponentBase *> &instances = mapIt->second;
    instances.erase(std::remove(instances.begin(), instances.end(), this), instances.end());

    if (instances.empty())
    {
        registry.erase(mapIt);
    }

    m_isRegistered = false;
}
