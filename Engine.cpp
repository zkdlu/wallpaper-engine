#include "Engine.h"

Engine::Engine()
	:m_hWnd(0)
{
	HDC screenDC = ::GetDC(NULL);
	RESOLUTION_WIDTH = GetDeviceCaps(screenDC, HORZRES);
	RESOLUTION_HEIGHT = GetDeviceCaps(screenDC, VERTRES);
	::ReleaseDC(0, screenDC);
}

Engine::~Engine()
{
}

BOOL CALLBACK Engine::enumWndProc(HWND hWnd, LPARAM lParam)
{
	Engine* engine = reinterpret_cast<Engine *>(lParam);

	if (FindWindowEx(hWnd, 0, TEXT("SELLDLL_DefView"), 0))
	{
		engine->m_hWnd = FindWindowEx(0, hWnd, TEXT("WorkerW"), 0);
	}

	return TRUE;
}

bool Engine::FindHWnd()
{
	m_hWnd = 0;

	HWND hWndProgram = FindWindow(TEXT("Progman"), 0);

	if (hWndProgram == 0)
	{
		return FALSE;
	}

	SendMessageTimeout(hWndProgram, 0x052c, 0, 0, SMTO_NORMAL, 1000, nullptr);

	EnumWindows(&Engine::enumWndProc,
		reinterpret_cast<LPARAM>(this));

	return m_hWnd != 0;
}

HWND Engine::GetHWnd()const
{
	return m_hWnd;
}

HDC Engine::GetDC() const
{
	return GetDCEx(m_hWnd, 0, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE);
}

void Engine::ReleaseDC(HDC hdc)
{
	::ReleaseDC(m_hWnd, hdc);
}

void Engine::SetVideo()
{
	capture = new VideoCapture();
}

bool Engine::PlayVideo()
{
	Mat frame;

	if (capture->isOpened())
	{
		return capture->read(frame);
	}

	return false;
}