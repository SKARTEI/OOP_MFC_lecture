
// ListCtrlTest2View.h: CListCtrlTest2View 클래스의 인터페이스
//

#pragma once


class CListCtrlTest2View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CListCtrlTest2View() noexcept;
	DECLARE_DYNCREATE(CListCtrlTest2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_LISTCTRLTEST2_FORM };
#endif

// 특성입니다.
public:
	CListCtrlTest2Doc* GetDocument() const;

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
	virtual ~CListCtrlTest2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPrintIndex();
};

#ifndef _DEBUG  // ListCtrlTest2View.cpp의 디버그 버전
inline CListCtrlTest2Doc* CListCtrlTest2View::GetDocument() const
   { return reinterpret_cast<CListCtrlTest2Doc*>(m_pDocument); }
#endif

