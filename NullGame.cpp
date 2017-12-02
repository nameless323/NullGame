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
    }
    ~TestSceneSystem()
    {
    }
};

void OnEngineInit()
{
    Kioto::Scene* scene = new TestScene();
    scene->AddSystem(new TestSceneSystem{});
    Kioto::SetScene(scene);
}

void OnEngineShutdown()
{
    OutputDebugStringA("Engine shutdown");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int nCmdShow)
{
    Kioto::KiotoMain(hInstance, prevInstance, cmdLine, nCmdShow, L"Kioto game", OnEngineInit, OnEngineShutdown);
    return 0;
}
