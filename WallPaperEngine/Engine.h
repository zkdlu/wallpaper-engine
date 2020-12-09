#pragma once

#include <iostream>
#include <Windows.h>
#include <opencv\cv.hpp>

using namespace std;
using namespace cv;

class Engine
{
	HWND m_hWnd;

	VideoCapture *capture;
	Mat frame;

public:
	Engine();
	~Engine();

private:
	static BOOL CALLBACK enumWndProc(HWND hWnd, LPARAM lParam);

public:
	Mat GetFrame()const;

	bool FindHWnd();
	HWND GetHWnd()const;
	HDC GetDC()const;
	void ReleaseDC(HDC myDC);

	void SetVideo(string filePath);
	void SetStream();
	bool PlayVideo();
	void ReleaseCapture();
};