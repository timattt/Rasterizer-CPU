#pragma once

// Includes
#include <windows.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <wingdi.h>

#include "../Rasterizator/GraphicalContextGlobal.h"

// Functions
// window
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

// To implement
int SetFbPixel(int x, int y, int r, int g, int b);
int loadTexture(char* path, txtr_p * res);

// Test
int init();
int draw();
int destroy();
