
// WallPaperEngineDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "WallPaperEngine.h"
#include "WallPaperEngineDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWallPaperEngineDlg 대화 상자



CWallPaperEngineDlg::CWallPaperEngineDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_WALLPAPERENGINE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWallPaperEngineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CWallPaperEngineDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_FILE_OPEN, &CWallPaperEngineDlg::OnFileOpen)
	ON_COMMAND(ID_FILE_EXIT, &CWallPaperEngineDlg::OnFileExit)
	ON_COMMAND(ID_STREAM_START, &CWallPaperEngineDlg::OnStreamStart)
	ON_COMMAND(ID_STREAM_STOP, &CWallPaperEngineDlg::OnStreamStop)
	ON_WM_TIMER()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CWallPaperEngineDlg 메시지 처리기

BOOL CWallPaperEngineDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	CMenu menu;
	menu.LoadMenuW(IDR_MENU);
	SetMenu(&menu);

	HDC screenDC = ::GetDC(NULL);
	RESOLUTION_WIDTH = GetDeviceCaps(screenDC, HORZRES);
	RESOLUTION_HEIGHT = GetDeviceCaps(screenDC, VERTRES);
	::ReleaseDC(0, screenDC);

	engine = new Engine();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CWallPaperEngineDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CWallPaperEngineDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWallPaperEngineDlg::OnFileOpen()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	LPCTSTR nameFilter = _T("Image (*.GIF, *.JPG, *.mp4, *.avi) | *.GIF;*.JPG; *.mp4; *.avi | All Files(*.*)|*.*||");
	CFileDialog fileDialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, nameFilter, NULL, 0, TRUE);

	if (fileDialog.DoModal() == IDOK)
	{
		CString pathName = fileDialog.GetPathName();
		CString extensionName = pathName.Right(pathName.GetLength() - (pathName.ReverseFind('.') + 1));
		extensionName.MakeUpper();

		if (extensionName == "MP4" || extensionName == "AVI")
		{
			//engine
		}
		else if (extensionName == "JPG" || extensionName == "GIF")
		{
			//engine
		}

		CT2CA pszConvertedAnsiString(pathName);
		string filePath(pszConvertedAnsiString);

		engine->SetVideo(filePath);

		SetTimer(1, 30, NULL);
	}
}


void CWallPaperEngineDlg::OnFileExit()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(1);

	SendMessage(WM_CLOSE, 0, 0);
}


void CWallPaperEngineDlg::OnStreamStart()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	KillTimer(1);

	engine->SetStream();

	SetTimer(1, 30, NULL);
}


void CWallPaperEngineDlg::OnStreamStop()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	engine->ReleaseCapture();

	KillTimer(1);
}


void CWallPaperEngineDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (engine->PlayVideo())
	{
		if (engine->FindHWnd())
		{
			HDC hdc = engine->GetDC();

			if (hdc != 0)
			{
				Mat mat;
				resize(engine->GetFrame(), mat,
					Size(RESOLUTION_WIDTH, RESOLUTION_HEIGHT), 0, 0, CV_INTER_NN);

				BITMAPINFO bitmapInfo;
				bitmapInfo.bmiHeader.biBitCount = 8 * mat.elemSize();
				bitmapInfo.bmiHeader.biWidth = mat.cols;
				bitmapInfo.bmiHeader.biHeight = -mat.rows;
				bitmapInfo.bmiHeader.biPlanes = 1;
				bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
				bitmapInfo.bmiHeader.biCompression = BI_RGB;
				bitmapInfo.bmiHeader.biClrImportant = 0;
				bitmapInfo.bmiHeader.biClrUsed = 0;
				bitmapInfo.bmiHeader.biSizeImage = 0;
				bitmapInfo.bmiHeader.biXPelsPerMeter = 0;
				bitmapInfo.bmiHeader.biYPelsPerMeter = 0;

				SetDIBitsToDevice(hdc,
					0, 0, mat.cols, mat.rows,
					0, 0, 0, mat.rows,
					mat.data, &bitmapInfo, DIB_RGB_COLORS);

				mat.release();
				engine->ReleaseDC(hdc);
			}
		}
	}

	CDialog::OnTimer(nIDEvent);
}


void CWallPaperEngineDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	KillTimer(1);
	engine->ReleaseCapture();
	engine->ReleaseDC(engine->GetDC());
}
