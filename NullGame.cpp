//
// Copyright (C) Alexandr Vorontsov. 2017
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).
//

#include "stdafx.h"

#include <Kioto.h>

#include <windows.h>

void OnEngineInited()
{
    Kioto::Scene* scene = new Kioto::Scene();
    Kioto::SetScene(scene);
    OutputDebugStringA("init engine");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int nCmdShow)
{
    Kioto::KiotoMain(hInstance, prevInstance, cmdLine, nCmdShow, L"Kioto game", OnEngineInited);
    return 0;
}
