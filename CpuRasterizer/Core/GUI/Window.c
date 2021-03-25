#include "Window.h"
#include "../Graphics/Rasterizer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, INT nCmdShow) {
	MSG msg;
	WNDCLASSW wc = { 0 };

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"Draw Bitmap";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	CreateWindowW(wc.lpszClassName, L"Draw Bitmap",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE, WIDTH / 4, HEIGHT / 4, WIDTH, HEIGHT,
			NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

#define SET_PIX(X, Y, r, g, b) pixs[4 * (X + Y * HEIGHT)] = b; pixs[4 * (X + Y * HEIGHT) + 1] = g; pixs[4 * (X + Y * HEIGHT) + 2] = r;
#define SET_PIX_CVV(X, Y, r, g, b) SET_PIX((X + WIDTH / 2), (HEIGHT / 2 - Y), r, g, b);

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HBITMAP bitmap;
	static char pixs[4 * WIDTH * HEIGHT] = {0};
	static int idTimer = -1;
	static BITMAPINFO  bmpinfo = {0};
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hdcMem;
	HGDIOBJ oldBitmap;

	switch (msg) {

	case WM_CREATE:
		hdc = GetDC(hwnd);
		bitmap = (HBITMAP) CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
		SetTimer(hwnd, idTimer = 1, 10, NULL);

		bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFO) - sizeof(RGBQUAD);
		bmpinfo.bmiHeader.biWidth = WIDTH;
		bmpinfo.bmiHeader.biHeight = -HEIGHT;
		bmpinfo.bmiHeader.biPlanes = 1;
		bmpinfo.bmiHeader.biBitCount = 32;
		bmpinfo.bmiHeader.biCompression = BI_RGB;
		bmpinfo.bmiHeader.biSizeImage = 0;
		bmpinfo.bmiHeader.biXPelsPerMeter = 0;
		bmpinfo.bmiHeader.biYPelsPerMeter = 0;
		bmpinfo.bmiHeader.biClrUsed = 0;
		bmpinfo.bmiHeader.biClrImportant = 0;

		break;

	case WM_TIMER:
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, bitmap);

		// DRAW
		for (int x = -WIDTH / 2; x < WIDTH / 2; x++) {
			for (int w = -2; w < 3; w++) {
				SET_PIX_CVV(x, w, 0, 255, 0);
				SET_PIX_CVV(w, x, 0, 255, 0);
			}
		}
		for (int x = 0; x < 30; x++) {
			for (int y = 0; y < 30; y++) {
				SET_PIX_CVV(x, y, 255, 0, 0);
			}
		}

		SetDIBits(hdcMem, bitmap, 0, HEIGHT, pixs, &bmpinfo, DIB_RGB_COLORS);

		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0,
		SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		KillTimer(hwnd, idTimer);
		DeleteObject(bitmap);
		PostQuitMessage(0);

		return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}
