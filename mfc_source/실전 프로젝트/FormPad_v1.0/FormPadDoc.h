
// FormPadDoc.h: CFormPadDoc 클래스의 인터페이스
//


#pragma once


class CFormPadDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CFormPadDoc() noexcept;
	DECLARE_DYNCREATE(CFormPadDoc)

// 특성입니다.
public:
	CObList &GetControlList()	{ return m_listControl; }

// 작업입니다.
public:
	POSITION AddControl(CObject *pObj)
	{
		return m_listControl.AddTail(pObj);
	}
	void RemoveControl(CObject *pObj)
	{
		POSITION pos = m_listControl.Find(pObj);
		if (pos != NULL)
			m_listControl.RemoveAt(pos);
	}
	void LookUpControl(CObList &list, CRuntimeClass *pClass)
	{
		list.RemoveAll();
		POSITION pos = m_listControl.GetHeadPosition();
		while ( pos != NULL )
		{
			CObject *pObj = m_listControl.GetNext(pos);
			if ( pObj->IsKindOf(pClass) == TRUE )
				list.AddTail(pObj);
		}
	}

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CFormPadDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CObList		m_listControl;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
