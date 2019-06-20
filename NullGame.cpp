//
// Copyright (C) Aleksandr Vorontcov. 2017
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).
//

#include "stdafx.h"

#include <Kioto.h>

#include <sstream>

class TestScene : public Kioto::Scene
{
public:
    ~TestScene()
    {
    }
};

Kioto::TransformComponent* cameraTransform = new Kioto::TransformComponent();
Kioto::CameraComponent* cam;

Kioto::TransformComponent* teapotTransform = new Kioto::TransformComponent();

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
        teapotTransform->SetWorldPosition({ left, 0.0f, fwd });
        std::stringstream ss;
        //auto mouse = Kioto::Input::GetMouseRelativePosition(); //<-- check all buttons
        //    ss << __FILE__ << "(" << __LINE__ << ")" << " x: " << mouse.x << " | y: " << mouse.y << std::endl;
        if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeA))
            left -= 5.0f * dt;
        else if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeD))
            left += 5.0f * dt;
        else if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeW))
            fwd += 5.0f * dt;
        else if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeS))
            fwd -= 5.0f * dt;

        Kioto::Matrix4 rot = Kioto::Matrix4::Identity;
        if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeJ))
            rotY -= 25.0f * dt;
        else if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeL))
            rotY += 25.0f * dt;
        else if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeI))
            rotX += 25.0f * dt;
        else if (Kioto::Input::GetIsButtonHeldDown(Kioto::eKeyCode::KeyCodeK))
            rotX -= 25.0f * dt;
        rot *= Kioto::Matrix4::BuildRotationX(Kioto::Math::DegToRad(rotX)) * Kioto::Matrix4::BuildRotationY(Kioto::Math::DegToRad(rotY));
        teapotTransform->SetWorldRotation(rot);

        if (Kioto::Input::GetButtonUp(Kioto::eKeyCode::KeyCodeSpace))
        {
            fwd = 1.0f;
            left = 0.0f;

            rotX = 0.0f;
            rotY = 0.0f;
        }
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
    Kioto::Scene* scene = new TestScene();
    Kioto::SetScene(scene);

    Kioto::Entity* cameraEntity = new Kioto::Entity();
    cameraEntity->SetName("Camera");
    cameraEntity->AddComponent(cameraTransform);

    cam = new Kioto::CameraComponent(Kioto::Math::DegToRad(60.0f), Kioto::Renderer::GetAspect(), 0.01f, 100.0f);
    cam->SetIsMain(true);
    cameraEntity->AddComponent(cam);
    cameraTransform->SetWorldRotation(Kioto::Matrix4::Identity);
    cameraTransform->SetWorldPosition({ 0.0f, 0.0f, -5.0f });

    scene->AddSystem(new TestSceneSystem{});
    scene->AddEntity(cameraEntity);

    Kioto::Entity* teapotEntity = new Kioto::Entity();
    teapotEntity->SetName("Teapot");
    teapotTransform->SetWorldPosition({ 1.0f, 0.0f, 2.0f });
    teapotEntity->AddComponent(teapotTransform);

    Kioto::RenderComponent* teapotRenderer = new Kioto::RenderComponent();
    teapotRenderer->SetMaterial("Materials\\Test.mt");
    teapotRenderer->SetMesh("Models\\Teapot.fbx");
    teapotEntity->AddComponent(teapotRenderer);

    scene->AddEntity(teapotEntity);
}

void OnEngineShutdown()
{
}

RUN_KIOTO;