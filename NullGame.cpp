//
// Copyright (C) Alexandr Vorontsov. 2017
// Distributed under the MIT License (license terms are at http://opensource.org/licenses/MIT).
//

#include "stdafx.h"

#include <Core\KiotoEngine.h>

#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int nCmdShow)
{
    Kioto::KiotoMain(hInstance, prevInstance, cmdLine, nCmdShow);
    return 0;
}
