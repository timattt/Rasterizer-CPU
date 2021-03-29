#include "../GUITest/TestWindow.h"

// Local variables
char pixs[4 * WIDTH * HEIGHT] = { 0 };
HWND hwnd = { 0 };
BITMAPINFO bmpinfo = { 0 };

// Local defines
#define SET_PIX(X, Y, r, g, b)  pixs[4 * (X + Y * HEIGHT)] = b; \
								pixs[4 * (X + Y * HEIGHT) + 1] = g; \
								pixs[4 * (X + Y * HEIGHT) + 2] = r;   //red
#define SET_PIX_CVV(X, Y, r, g, b) SET_PIX((X + WIDTH / 2), (HEIGHT / 2 - Y), r, g, b);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPSTR lpCmdLine, INT nCmdShow) {
	MSG msg;
	WNDCLASSW wc = { 0 };

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

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpszClassName = L"Draw Bitmap";
	wc.hInstance = hInstance;
	wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
	wc.lpfnWndProc = WndProc;
	wc.hCursor = LoadCursor(0, IDC_ARROW);

	RegisterClassW(&wc);
	hwnd = CreateWindowW(wc.lpszClassName, L"Draw Bitmap",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE, WIDTH / 4, HEIGHT / 4, WIDTH,
			HEIGHT, NULL, NULL, hInstance, NULL);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int) msg.wParam;
}

int SetFbPixel(int x, int y, int r, int g, int b) {
	if (x <= - WIDTH / 2 || x >= WIDTH / 2 || y <= -HEIGHT / 2
			|| y >= HEIGHT / 2) {
		printf("bad coords for setfb pixel!\b");
		exit(-1);
	}
	SET_PIX_CVV(x, y, r, g, b);
	return 0;
}

void flush() {
	for (int x = 0; x < 4 * WIDTH * HEIGHT; x++) {
		pixs[x] = 0;
	}
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HBITMAP bitmap;
	static int idTimer = -1;
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hdcMem = { 0 };
	HGDIOBJ oldBitmap;

	switch (msg) {

	case WM_CREATE:
		hdc = GetDC(hwnd);
		bitmap = (HBITMAP) CreateCompatibleBitmap(hdc, WIDTH, HEIGHT);
		SetTimer(hwnd, idTimer = 1, 10, NULL);

		init();
		break;

	case WM_TIMER:
		InvalidateRect(hwnd, NULL, FALSE); //PostMessage(hwnd, WM_PAINT, 0, 0);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);

		hdcMem = CreateCompatibleDC(hdc);
		oldBitmap = SelectObject(hdcMem, bitmap);

#ifdef PRINT_TIME
		int delta = 0;
		clock_t before = clock();
#endif

		// DRAW
		//---------------
		flush();
		draw();
		//---------------

#ifdef PRINT_TIME
		clock_t difference = clock() - before;
		delta = difference * 1000 / CLOCKS_PER_SEC;
		printf("%d milsec per tick!\n", delta);
#endif

		SetDIBits(hdcMem, bitmap, 0, HEIGHT, pixs, &bmpinfo, DIB_RGB_COLORS);

		BitBlt(hdc, 0, 0, WIDTH, HEIGHT, hdcMem, 0, 0,
		SRCCOPY);

		SelectObject(hdcMem, oldBitmap);
		DeleteDC(hdcMem);

		EndPaint(hwnd, &ps);

		break;

	case WM_DESTROY:
		destroy();
		KillTimer(hwnd, idTimer);
		DeleteObject(bitmap);
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcW(hwnd, msg, wParam, lParam);
}

int loadTexture(char *path, txtr_p *res) {
	HBITMAP bm = (HBITMAP) LoadImageW(NULL, (LPCWSTR)path,
	IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	if (bm == NULL) {
		printf("bmp load error!\n");
		exit(-1);
	}

	BITMAP bitmap = {0};
	GetObject(bm, sizeof(bitmap), &bitmap);

	HDC hdcMem = CreateCompatibleDC(GetDC(hwnd));

	SelectObject(hdcMem, bm);

	int width = bitmap.bmWidth;
	int height = bitmap.bmHeight;
	char * pixels = malloc(4 * width * height);
	memset(pixels, 0, 4 * width * height);

	BITMAPINFO bmpinfo = { 0 };

	bmpinfo.bmiHeader.biSize = sizeof(BITMAPINFO);
	bmpinfo.bmiHeader.biWidth = width;
	bmpinfo.bmiHeader.biHeight = height;
	bmpinfo.bmiHeader.biPlanes = 1;
	bmpinfo.bmiHeader.biBitCount = 32;
	bmpinfo.bmiHeader.biCompression = BI_RGB;
	bmpinfo.bmiHeader.biSizeImage = 0;
	bmpinfo.bmiHeader.biXPelsPerMeter = 0;
	bmpinfo.bmiHeader.biYPelsPerMeter = 0;
	bmpinfo.bmiHeader.biClrUsed = 0;
	bmpinfo.bmiHeader.biClrImportant = 0;

	GetDIBits(hdcMem, bm, 0, height, pixels, &bmpinfo, DIB_PAL_COLORS);

	CreateTexture(width, height, pixels, res);

	DeleteDC(hdcMem);
	DeleteObject(bm);
	return 0;
}
