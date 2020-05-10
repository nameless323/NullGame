//
// Copyright (C) Aleksandr Vorontcov. 2017
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).
//

#include "stdafx.h"

#include <Kioto.h>

#include <sstream>
#include <iostream>

class TestScene : public Kioto::Scene
{
public:
    TestScene(std::string name)
        : Scene(name)
    {
    }

    ~TestScene()
    {
    }
};

Kioto::TransformComponent* cameraTransform = new Kioto::TransformComponent();

class TestSceneSystem : public Kioto::SceneSystem
{
public:
    void OnEntityAdd(Kioto::Entity* entity) override
    {

    }
    void OnEntityRemove(Kioto::Entity* entity) override
    {

    }
    void Update(float32 dt) override
    {
        using namespace Kioto;

        Vector3 thisFrameOffset;
        float32 mouseAccel = 0.02f;
        float32 mouseRotationAccel = 0.2f;

        std::stringstream ss;
        eMouseWheelScroll scroll = Input::GetMouseWheel();
        if (scroll == eMouseWheelScroll::ScrollUp)
            thisFrameOffset.z += 0.5f;
        else if (scroll == eMouseWheelScroll::ScrollDown)
            thisFrameOffset.z -= 0.5f;

        if (Input::GetIsButtonHeldDown(eKeyCode::KeyCodeControl))
            mouseAccel *= 10;

        Vector2i mouseRelativePosition = Input::GetMouseRelativePosition();
        if (Input::GetMouseHeldDown(eMouseCodes::MouseMiddle))
        {
            thisFrameOffset.x = mouseRelativePosition.x * -mouseAccel;
            thisFrameOffset.y = mouseRelativePosition.y * mouseAccel;
        }

        Matrix4 worldRotation = Matrix4::Identity;

        static float32 xAccum = 0; 
        static float32 yAccum = 0;
        if (scroll == eMouseWheelScroll::ScrollNone && Input::GetMouseHeldDown(Kioto::eMouseCodes::MouseRight))
        {
            xAccum += mouseRelativePosition.y * mouseRotationAccel;
            yAccum += mouseRelativePosition.x * mouseRotationAccel;
        }
        Matrix4 xRot = Matrix4::BuildRotationX(Kioto::Math::DegToRad(xAccum));
        Matrix4 yRot = Matrix4::BuildRotationY(Kioto::Math::DegToRad(yAccum));
        worldRotation = yRot * xRot;

        Vector3 worldPos = cameraTransform->TransformPointToWorld(thisFrameOffset);

        cameraTransform->SetWorldPosition(worldPos);
        cameraTransform->SetWorldRotation(worldRotation);
    }
    ~TestSceneSystem()
    {
    }

    float32 fwd = 1.0f;
    float32 left = 0.0f;

    float32 rotX = 0.0f;
    float32 rotY = 0.0f;
};

void OnEngineInit()
{
    Kioto::LoadScene("C:\\Repos\\NullGame\\scenes\\scene.ksc");
    Kioto::Scene* scene = Kioto::GetScene();
    scene->AddSystem(new TestSceneSystem{});
    Kioto::Entity* cameraEntity = scene->FindEntity("Camera");
    cameraTransform = cameraEntity->GetTransform();
}

void OnEngineShutdown()
{
}

RUN_KIOTO;