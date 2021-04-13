
// MainFrm.h: CMainFrame 클래스의 인터페이스
//

#pragma once

#include "ControlToolBar.h"

class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	BOOL& GetMode() { return m_bRunMode; }

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 컨트롤 모음이 포함된 멤버입니다.
	CControlToolBar   m_wndToolBar;
	CStatusBar        m_wndStatusBar;

protected:
	BOOL			m_bRunMode;
	const int		m_iDifference;

// 생성된 메시지 맵 함수
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void CMainFrame::OnControl(UINT nID);
	afx_msg void CMainFrame::OnUpdateButton32781(CCmdUI*pCmdUI);
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnModeEdit();
	afx_msg void OnModeRun();
	afx_msg void OnUpdateModeEdit(CCmdUI* pCmdUI);
	afx_msg void OnUpdateModeRun(CCmdUI* pCmdUI);
};


