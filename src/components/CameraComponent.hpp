#pragma once

#include "components/Component.hpp"

class CameraComponent : public Component
{
    float m_zoom;
    float m_rotation;

    float m_lastZoom;
    float m_lastRotation;
    raylib::Vector3 m_lastPos;

    raylib::Color m_bgColor;

    void UpdateMatrix();

public:
    static CameraComponent *m_mainCam;
    static CameraComponent *GetMainCam();

    raylib::Matrix m_matrix;
    CameraComponent(Color bgColor = BLACK);
    ~CameraComponent();

    virtual void Init(GameObject *owner);
    virtual void Update();
    virtual void Destroy();

    void SetPos(raylib::Vector2 pos);

    void PushMatrix();

    raylib::Vector2 GetMousePos();
};