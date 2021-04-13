
// OLEDB2View.h : COLEDB2View 클래스의 인터페이스
//

#pragma once

class COLEDB2Set;

class COLEDB2View : public COleDBRecordView
{
protected: // serialization에서만 만들어집니다.
	COLEDB2View();
	DECLARE_DYNCREATE(COLEDB2View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_OLEDB2_FORM };
#endif
	COLEDB2Set* m_pSet;

// 특성입니다.
public:
	COLEDB2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual CRowset<>* OnGetRowset();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~COLEDB2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // OLEDB2View.cpp의 디버그 버전
inline COLEDB2Doc* COLEDB2View::GetDocument() const
   { return reinterpret_cast<COLEDB2Doc*>(m_pDocument); }
#endif

