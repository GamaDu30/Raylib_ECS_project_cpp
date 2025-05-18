#pragma once

#include "definitions.hpp"
#include "components/Component.hpp"

class TransformComponent : public Component
{
    raylib::Vector3 m_pos = raylib::Vector3();
    float m_rotation = 0.f;
    raylib::Vector2 m_scale = raylib::Vector2(1, 1);

    raylib::Vector3 m_lastPos = raylib::Vector3();
    float m_lastRotation = 0.f;
    raylib::Vector2 m_lastScale = raylib::Vector2(1, 1);

    raylib::Matrix m_matrix;

    bool m_isDirty = false;

    std::vector<TransformComponent *> m_children = {};
    TransformComponent *m_parent = nullptr;

    void UpdateLocalMatrix();

public:
    TransformComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    raylib::Vector3 &GetPos();
    raylib::Vector2 &GetScale();
    float &GetRotation();

    void SetDirty();

    void AddChild(TransformComponent *newChild);
    void RemoveChild(TransformComponent *childToRemove);
    void RemoveChild(int id);

    std::vector<TransformComponent *> GetChildren();
    TransformComponent *GetChild(int id);

    void SetParent(TransformComponent *newParent);

    raylib::Matrix GetMatrix();
    void PushMatrix();
};