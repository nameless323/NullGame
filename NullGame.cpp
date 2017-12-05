//
// Copyright (C) Alexandr Vorontsov. 2017
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).
//

#include "stdafx.h"

#include <Kioto.h>

#include <windows.h>

class TestScene : public Kioto::Scene
{
public:
    ~TestScene()
    {
    }
};

Kioto::TransformComponent* tc = new Kioto::TransformComponent();
Kioto::CameraComponent* cam;

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
        p -= dt;
        tc->SetWorldPosition({ 0.0f, 0.0f, p });
        if (p < -5.0f)
            p = -1.0f;
    }
    ~TestSceneSystem()
    {
    }

    float32 p = -1.0f;
};

void OnEngineInit()
{
    Kioto::Scene* scene = new TestScene();
    Kioto::SetScene(scene);

    Kioto::Entity* e = new Kioto::Entity();
    e->AddComponent(tc);

    cam = new Kioto::CameraComponent(Kioto::Math::DegToRad(60.0f), Kioto::Renderer::GetAspect(), 0.01f, 100.0f);
    cam->SetIsMain(true);
    e->AddComponent(cam);
    tc->SetWorldRotation(Kioto::Matrix4::Identity);
    tc->SetWorldPosition({ 0.0f, 0.0f, -1.0f });

    scene->AddSystem(new TestSceneSystem{});
    scene->AddEntity(e);
}

void OnEngineShutdown()
{
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int nCmdShow)
{
    Kioto::KiotoMain(hInstance, prevInstance, cmdLine, nCmdShow, L"Kioto game", OnEngineInit, OnEngineShutdown);
    return 0;
}
