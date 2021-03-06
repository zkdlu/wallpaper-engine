
// WallPaperEngineDlg.h: 헤더 파일
//

#pragma once

#include "Engine.h"

// CWallPaperEngineDlg 대화 상자
class CWallPaperEngineDlg : public CDialog
{
// 생성입니다.
public:
	CWallPaperEngineDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WALLPAPERENGINE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileExit();
	afx_msg void OnStreamStart();
	afx_msg void OnStreamStop();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnDestroy();

private:

	int RESOLUTION_WIDTH;
	int RESOLUTION_HEIGHT;

	Engine *engine;
};
