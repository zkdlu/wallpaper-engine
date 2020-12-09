#include "WallPaperEngine.h"

WallPaperEngine::WallPaperEngine()
	:m_hWnd(0)
{
	capture = NULL;

	HDC screenDC = ::GetDC(NULL);
	RESOLUTION_WIDTH = GetDeviceCaps(screenDC, HORZRES);
	RESOLUTION_HEIGHT = GetDeviceCaps(screenDC, VERTRES);
	::ReleaseDC(0, screenDC);
}

WallPaperEngine::~WallPaperEngine()
{
}

BOOL CALLBACK WallPaperEngine::enumWndProc(HWND hWnd, LPARAM lParam)
{
	WallPaperEngine* engine = reinterpret_cast<WallPaperEngine *>(lParam);

	if (FindWindowEx(hWnd, 0, TEXT("SELLDLL_DefView"), 0))
	{
		engine->m_hWnd = FindWindowEx(0, hWnd, TEXT("WorkerW"), 0);
	}

	return TRUE;
}

bool WallPaperEngine::FindHWnd()
{
	m_hWnd = 0;

	HWND hWndProgram = FindWindow(TEXT("Progman"), 0);

	if (hWndProgram == 0)
	{
		return FALSE;
	}

	SendMessageTimeout(hWndProgram, 0x052c, 0, 0, SMTO_NORMAL, 1000, nullptr);

	EnumWindows(&WallPaperEngine::enumWndProc,
		reinterpret_cast<LPARAM>(this));

	return m_hWnd != 0;
}

HWND WallPaperEngine::GetHWnd()const
{
	return m_hWnd;
}

HDC WallPaperEngine::GetDC() const
{
	return GetDCEx(m_hWnd, 0, DCX_WINDOW | DCX_CACHE | DCX_LOCKWINDOWUPDATE);
}

void WallPaperEngine::ReleaseDC(HDC hdc)
{
	::ReleaseDC(m_hWnd, hdc);
}