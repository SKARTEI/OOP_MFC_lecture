
// FormPadView.h: CFormPadView 클래스의 인터페이스
//

#pragma once


class CFormPadView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CFormPadView() noexcept;
	DECLARE_DYNCREATE(CFormPadView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_FORMPAD_FORM };
#endif

// 특성입니다.
public:
	CFormPadDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CFormPadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CRect	m_rectOld;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg LRESULT OnControlDown(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnControlDrag(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnControlDrop(WPARAM wParam, LPARAM lParam);
};

#ifndef _DEBUG  // FormPadView.cpp의 디버그 버전
inline CFormPadDoc* CFormPadView::GetDocument() const
   { return reinterpret_cast<CFormPadDoc*>(m_pDocument); }
#endif

