#pragma once

#include <Windows.h>
#include <opencv\cv.hpp>

using namespace cv;

class WallPaperEngine
{
	HWND m_hWnd;
	VideoCapture *capture;

	static int RESOLUTION_WIDTH;
	static int RESOLUTION_HEIGHT;

public:
	WallPaperEngine();
	~WallPaperEngine();

private:
	static BOOL CALLBACK enumWndProc(HWND hWnd, LPARAM lParam);

public:
	bool FindHWnd();
	HWND GetHWnd() const;
	HDC GetDC() const;
	void ReleaseDC(HDC hdc);
};