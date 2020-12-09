#include "Engine.h"

Engine::Engine()
	:m_hWnd(0)
{
}


Engine::~Engine()
{
}

BOOL CALLBACK Engine::enumWndProc(HWND hWnd, LPARAM lParam)
{
	auto *me = reinterpret_cast<Engine *>(lParam);

	if (FindWindowEx(hWnd, 0, TEXT("SHELLDLL_DefView"), 0))
	{
		me->m_hWnd = FindWindowEx(0, hWnd, TEXT("WorkerW"), 0);
	}

	return TRUE;
}

bool Engine::FindHWnd()
{
	m_hWnd = 0;

	HWND hWndProgram = FindWindow(TEXT("Progman"), nullptr);

	if (hWndProgram == 0)
	{
		return false;
	}

	SendMessageTimeout(hWndProgram, 0x052C, 0, 0, SMTO_NORMAL, 1000, nullptr);

	EnumWindows(&Engine::enumWndProc,
		reinterpret_cast<LPARAM>(this));

	return (m_hWnd != 0);
}

HWND Engine::GetHWnd()const
{
	return m_hWnd;
}

HDC Engine::GetDC()const
{
	return GetDCEx(m_hWnd, 0, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE);
}

void Engine::ReleaseDC(HDC myDC)
{
	::ReleaseDC(m_hWnd, myDC);
}

void Engine::SetVideo(string filePath)
{
	capture = new VideoCapture(filePath);
}

void Engine::SetStream()
{
	capture = new VideoCapture(0);
}

bool Engine::PlayVideo()
{
	if (capture->isOpened())
	{
		return capture->read(frame);
	}

	return false;
}

void Engine::ReleaseCapture()
{
	if (capture->isOpened())
	{
		capture->release();
	}
}

Mat Engine::GetFrame()const
{
	return frame;
}