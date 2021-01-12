//
// Copyright (C) Aleksandr Vorontcov. 2017
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).
//

#include "stdafx.h"

#include <Kioto.h>

#include <sstream>
#include <iostream>

#include "Gameplay/CameraMovementController.h"

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
using namespace NullGame;

Kioto::TransformComponent* cameraTransform = nullptr;
NullGame::CameraMovementController* cameraMovementController = nullptr;

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
        cameraMovementController->Update(dt);
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
    cameraMovementController = new CameraMovementController(cameraTransform, 0.02f, 0.2f, 0.5f, 0.01f);
}

void OnEngineShutdown()
{
    delete cameraMovementController;
}

RUN_KIOTO;