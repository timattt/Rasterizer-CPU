#pragma once

// Includes
#include <windows.h>
#include <stdio.h>

#include "../Rasterizator/GraphicalContextGlobal.h"

// Functions
// window
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int SetFbPixel(int x, int y, int r, int g, int b);

// Test
int init();
int draw();
int destroy();
