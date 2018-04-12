#pragma once
#include "common.h"
#include "stdafx.h"
#include "windows.h"
struct COMPLEX
{
	double re;
	double im;
};
COMPLEX operator * (COMPLEX a, COMPLEX b)
{
	COMPLEX c;
	c.re = a.re * b.re - a.im * b.im;
	c.im = a.im * b.re + a.re * b.im;
	return c;
}
// 定义复数“加”运算
COMPLEX operator + (COMPLEX a, COMPLEX b)
{
	COMPLEX c;
	c.re = a.re + b.re;
	c.im = a.im + b.im;
	return c;
}

class julia_mandel
{
public:
	julia_mandel(int width,int height) {
		windows_width = width;
		windows_height = height;
#ifdef SHOW_PRINT
		hdc = gethdc();
#endif // SHOW_PRINT

	};
	double julia_test();
	double mandel_test();

private:
	HINSTANCE hInstance;
	WNDCLASS Draw;
	PAINTSTRUCT ps;
	HDC hdc;
	HWND hwnd;
	HDC gethdc();
	static LRESULT CALLBACK  WindowProc(
		_In_  HWND hwnd,
		_In_  UINT uMsg,
		_In_  WPARAM wParam,
		_In_  LPARAM lParam
	);
	void julia_test(COMPLEX c, int w, int h, char * buff);
	void mandel_test(int w, int h, char *buff);
	int windows_width;
	int windows_height;
	CStopWatch timer;
};

LRESULT CALLBACK julia_mandel::WindowProc(
	_In_  HWND hwnd,
	_In_  UINT uMsg,
	_In_  WPARAM wParam,
	_In_  LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

HDC julia_mandel::gethdc()
{
    hInstance = GetModuleHandle(NULL);
	Draw.cbClsExtra = 0;
	Draw.cbWndExtra = 0;
	Draw.hCursor = LoadCursor(hInstance, IDC_ARROW);;
	Draw.hIcon = LoadIcon(hInstance, IDI_APPLICATION);;
	Draw.lpszMenuName = NULL;
	Draw.style = CS_HREDRAW | CS_VREDRAW;
	Draw.hbrBackground = (HBRUSH)COLOR_WINDOW;
	Draw.lpfnWndProc = WindowProc;
	Draw.lpszClassName = _T("DDraw");
	Draw.hInstance = hInstance;
	RegisterClass(&Draw);
	 hwnd = CreateWindow(
		_T("DDraw"),
		NULL,
		WS_OVERLAPPEDWINDOW,
		28,
		40,
		windows_width,
		windows_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, SW_SHOW);
	PAINTSTRUCT ps;
	return  BeginPaint(hwnd, &ps);
}

void julia_mandel::julia_test(COMPLEX c, int w, int h, char * buff)
{
	int i, j, offset = 0;
	unsigned char k, v = 0;
	COMPLEX z;
	for (i = 0; i <w; i++)
	{
		for (j = 0; j < h; j++)
		{
			z.re = -1.6 + 3.2 * (i / (float)w);
			z.im = -1.2 + 2.4 * (j / (float)h);
			for (k = 0; k < 200; k++)
			{

				if (z.re * z.re + z.im * z.im > 4.0)
				{
					break;
				}
				z = z*z + c;
			}
			*(char *)((ULONG64)buff + i*h + j) = k;
			offset++;
		}
	}
}
void julia_mandel::mandel_test(int w, int h, char *buff)
{
	int i, j, offset = 0;
	unsigned char k;
	COMPLEX z, c;
	for (i = 0; i < w; i++)
	{
		for (j = 0; j < h; j++)
		{
			z.re = 0;
			z.im = 0;
			c.re = -1.6 + 3.2 * (i / (float)w);
			c.im = -1.2 + 2.4 * (j / (float)h);
			for (k = 0; k < 200; k++)
			{
				if (z.re * z.re + z.im * z.im > 4.0)
				{
					break;
				}

				z = z*z + c;

			}
			*(char *)((ULONG64)buff + i*h + j) = k;

		}
	}

}
double julia_mandel::julia_test()
{
	double julia_time;
	int i, j;
	unsigned char k;
	float re[] = { -0.75,0.45,0.285,-0.8,-0.835,-0.70176 };
	float im[] = { 0,-0.1428,0.01,0,0.156,-0.2321,-0.3842 };
	char *buff_julia = (char *)malloc(windows_width*(windows_height + 1));
	COMPLEX c = { re[1],im[0] };
	timer.start();
	julia_test(c, windows_width, windows_height, buff_julia);
	timer.stop();
	julia_time = timer.getElapsedTime();

	
#ifdef SHOW_PRINT
printf("julia_time：%f\n", julia_time);
	for (i = 0; i<windows_width; i++)
		for (j = 0; j < windows_height; j++)
		{
			k = *(buff_julia + i*windows_height + j);
			BYTE r, g, b;
			g = k <= 70 ? k : 0;
			r = (k <= 10 & k > 160) ? k - 60 : 0;
			b = k > 160 ? k - 180 : 0;
			SetPixel(hdc, i, j, RGB(r * 25, g * 25, b * 4));

		}
#endif // SHOW_PRINT
	free(buff_julia);
	return julia_time;
}

double julia_mandel::mandel_test()
{
	double mandel_time;
	int i, j;
	unsigned char k;
	char *buff_mandel = (char *)malloc(windows_width*(windows_height + 1));

	timer.start();
	mandel_test(windows_width, windows_height, buff_mandel);
	timer.stop();
	mandel_time = timer.getElapsedTime();

#ifdef SHOW_PRINT
	printf("mandel_time：%f\n", mandel_time);
	for (i = 0; i<windows_width; i++)
		for (j = 0; j < windows_height; j++)
		{
			k = *(buff_mandel + i*windows_height + j);
			BYTE r, g, b;
			g = k <= 70 ? k : 0;
			r = (k <= 10 & k > 160) ? k - 60 : 0;
			b = k > 160 ? k - 180 : 0;
			SetPixel(hdc, i, j, RGB(r * 25, g * 25, b * 4));

		}

#endif // SHOW_PRINT
	free(buff_mandel);
	return mandel_time;

}


