
// ODBC2View.h : CODBC2View 클래스의 인터페이스
//

#pragma once

class CODBC2Set;

class CODBC2View : public CRecordView
{
protected: // serialization에서만 만들어집니다.
	CODBC2View();
	DECLARE_DYNCREATE(CODBC2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_ODBC2_FORM };
#endif
	CODBC2Set* m_pSet;

// 특성입니다.
public:
	CODBC2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual CRecordset* OnGetRecordset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CODBC2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ODBC2View.cpp의 디버그 버전
inline CODBC2Doc* CODBC2View::GetDocument() const
   { return reinterpret_cast<CODBC2Doc*>(m_pDocument); }
#endif

