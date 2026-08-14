#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <utility>
#include <vector>

template <typename... Args>
class Event
{
    struct HandlerEntry
    {
        std::size_t id;
        std::function<void(Args...)> fn;
    };

    std::vector<HandlerEntry> m_handlers = std::vector<HandlerEntry>();
    std::size_t m_nextId = 0;

public:
    Event() = default;
    ~Event() = default;

    template <typename Callable>
    std::size_t Add(Callable &&handler)
    {
        const std::size_t id = m_nextId++;
        m_handlers.push_back(HandlerEntry{id, std::function<void(Args...)>(std::forward<Callable>(handler))});
        return id;
    }

    bool Remove(std::size_t id);
    void Clear();

    void Invoke(Args... args);
};

template <typename... Args>
bool Event<Args...>::Remove(std::size_t id)
{
    std::size_t originalSize = m_handlers.size();

    m_handlers.erase(
        std::remove_if(
            m_handlers.begin(),
            m_handlers.end(),
            [id](const HandlerEntry &entry)
            {
                return entry.id == id;
            }),
        m_handlers.end());

    return m_handlers.size() < originalSize;
}

template <typename... Args>
void Event<Args...>::Clear()
{
    m_handlers.clear();
}

template <typename... Args>
void Event<Args...>::Invoke(Args... args)
{
    for (auto &handler : m_handlers)
    {
        if (handler.fn)
        {
            handler.fn(args...);
        }
    }
}