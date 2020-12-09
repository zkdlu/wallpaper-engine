#pragma once

#include <Windows.h>
#include <opencv\cv.hpp>

using namespace cv;

class Engine
{
	HWND m_hWnd;

	static int RESOLUTION_WIDTH;
	static int RESOLUTION_HEIGHT;

	VideoCapture *capture;

public:
	Engine();
	~Engine();

private:
	static BOOL CALLBACK enumWndProc(HWND hWnd, LPARAM lParam);

public:
	bool FindHWnd();
	HWND GetHWnd() const;
	HDC GetDC() const;
	void ReleaseDC(HDC hdc);

	void SetVideo();
	bool PlayVideo();
};