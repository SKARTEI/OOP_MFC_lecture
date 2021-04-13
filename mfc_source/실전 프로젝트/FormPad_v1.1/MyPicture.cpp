// MyPicture.cpp : 구현 파일입니다.
//

#include "pch.h"
#include "FormPad.h"
#include "MyPicture.h"

#include "ControlToolBar.h"


IMPLEMENT_SERIAL(CMyPicture, CObject, 1)

// LoadBMPImage	- Loads a BMP file and creates a bitmap GDI object
//		  also creates logical palette for it.
// Returns	- TRUE for success
// sBMPFile	- Full path of the BMP file
// bitmap	- The bitmap object to initialize
// pPal		- Will hold the logical palette. Can be NULL
BOOL LoadBMPImage( LPCTSTR sBMPFile, CBitmap& bitmap, CPalette *pPal )
{
	CFile file;
	if( !file.Open( sBMPFile, CFile::modeRead) )
		return FALSE;

	BITMAPFILEHEADER bmfHeader;

	// Read file header
	if (file.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return FALSE;

	// File type should be 'BM'
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
		return FALSE;

	// Get length of the remainder of the file and allocate memory
	DWORD nPackedDIBLen = (DWORD)file.GetLength() - sizeof(BITMAPFILEHEADER);
	HGLOBAL hDIB = ::GlobalAlloc(GMEM_FIXED, nPackedDIBLen);
	if (hDIB == 0)
		return FALSE;

	// Read the remainder of the bitmap file.
	if (file.Read((LPSTR)hDIB, nPackedDIBLen) != nPackedDIBLen )
	{
		::GlobalFree(hDIB);
		return FALSE;
	}

	BITMAPINFOHEADER &bmiHeader = *(LPBITMAPINFOHEADER)hDIB;
	BITMAPINFO &bmInfo = *(LPBITMAPINFO)hDIB ;

	// If bmiHeader.biClrUsed is zero we have to infer the number
	// of colors from the number of bits used to specify it.
	int nColors = bmiHeader.biClrUsed ? bmiHeader.biClrUsed : 
		1 << bmiHeader.biBitCount;

	LPVOID lpDIBBits;
	if( bmInfo.bmiHeader.biBitCount > 8 )
		lpDIBBits = (LPVOID)((LPDWORD)(bmInfo.bmiColors + bmInfo.bmiHeader.biClrUsed) + 
		((bmInfo.bmiHeader.biCompression == BI_BITFIELDS) ? 3 : 0));
	else
		lpDIBBits = (LPVOID)(bmInfo.bmiColors + nColors);

	// Create the logical palette
	if( pPal != NULL )
	{
		// Create the palette
		if( nColors <= 256 )
		{
			UINT nSize = sizeof(LOGPALETTE) + (sizeof(PALETTEENTRY) * nColors);
			LOGPALETTE *pLP = (LOGPALETTE *) new BYTE[nSize];

			pLP->palVersion = 0x300;
			pLP->palNumEntries = nColors;

			for( int i=0; i < nColors; i++)
			{
				pLP->palPalEntry[i].peRed = bmInfo.bmiColors[i].rgbRed;
				pLP->palPalEntry[i].peGreen = bmInfo.bmiColors[i].rgbGreen;
				pLP->palPalEntry[i].peBlue = bmInfo.bmiColors[i].rgbBlue;
				pLP->palPalEntry[i].peFlags = 0;
			}

			pPal->CreatePalette( pLP );

			delete[] pLP;
		}
	}

	CClientDC dc(NULL);
	CPalette* pOldPalette = NULL;
	if( pPal )
	{
		pOldPalette = dc.SelectPalette( pPal, FALSE );
		dc.RealizePalette();
	}

	HBITMAP hBmp = CreateDIBitmap( dc.m_hDC,		// handle to device context 
		&bmiHeader,	// pointer to bitmap size and format data 
		CBM_INIT,	// initialization flag 
		lpDIBBits,	// pointer to initialization data 
		&bmInfo,	// pointer to bitmap color-format data 
		DIB_RGB_COLORS);		// color-data usage 
	bitmap.Attach( hBmp );

	if( pOldPalette )
		dc.SelectPalette( pOldPalette, FALSE );

	::GlobalFree(hDIB);
	return TRUE;
}


// CMyPicture

CMyPicture::CMyPicture()
	: CControlBase( 3 )
	, m_strPath( m_Property.m_strPath )
	, m_iAction( m_Property.m_iAction )
	, m_pBitmap( NULL )
{
	m_iAction = 0;
	m_bitmapDefault.LoadBitmap( IDB_PICTURE_BIG );
	m_bitmapDefault.GetBitmap( &m_bmDefault );
}

CMyPicture::~CMyPicture()
{
	if (m_pBitmap)
	{
		delete m_pBitmap;
		m_pBitmap = NULL;
	}
}


BEGIN_MESSAGE_MAP(CMyPicture, CStatic)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_CONTEXTMENU()
END_MESSAGE_MAP()


// CMyPicture 메시지 처리기입니다.

void CMyPicture::Serialize (CArchive& ar)
{
	CStatic::Serialize(ar);
	if (ar.IsStoring())
		ar << m_strPath << m_iAction;
	else
		ar >> m_strPath >> m_iAction;
}

BOOL CMyPicture::Create(CRect &rect, CWnd *pParentWnd)
{
	rect.SetRect( rect.left, rect.top,
		rect.left + m_bmDefault.bmWidth,
		rect.top + m_bmDefault.bmHeight );

	BOOL bRtn = CStatic::Create( _T(""),
		WS_CHILD|WS_VISIBLE|SS_BITMAP|SS_CENTERIMAGE|SS_NOTIFY,
		rect, pParentWnd, 101 );
		
	SetBitmap( m_bitmapDefault );
	SetFont(pParentWnd->GetFont());
	return bRtn;
}

void CMyPicture::PostNcDestroy() 
{
	delete this;
	CStatic::PostNcDestroy();
}

void CMyPicture::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{ 
		CStatic::OnLButtonDown(nFlags, point);
	}
	else
	{
		m_bDragging = TRUE;

		::SetCursor( AfxGetApp()->LoadCursor(
			m_wndToolBar.GetImageAt(m_iIndex) ) );
		SetCapture();

		CRect rect;
		GetParent()->GetClientRect( rect );
		GetParent()->ClientToScreen( rect );
		::ClipCursor( rect );

		GetClientRect( rect );
		CRect rectHORZ( rect ), rectVERT( rect );
		rectHORZ.DeflateRect( RESIZE_POINT, 0 );
		rectVERT.DeflateRect( 0, RESIZE_POINT );
		if ( rectHORZ.PtInRect(point) == FALSE )
		{
			::SetCursor( ::LoadCursor(NULL, IDC_SIZEWE) );
			m_Resize = HORZ;
		}
		else if ( rectVERT.PtInRect(point) == FALSE )
		{
			::SetCursor( ::LoadCursor(NULL, IDC_SIZENS) );
			m_Resize = VERT;
		}
		else
		{
			m_Resize = NONE;
		}

		GetClientRect( rect );
		ClientToScreen( rect );
		m_ptHotspot = point;

		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DOWN,
			(WPARAM)&rect, NULL );
	}
	CStatic::OnLButtonDown(nFlags, point);
}

void CMyPicture::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ( m_bRunMode == TRUE )
	{
		CStatic::OnMouseMove(nFlags, point);
	}
	else if (m_bDragging == TRUE && nFlags & MK_LBUTTON)
	{
		CRect rect;
		GetClientRect( rect );

		CSize size( point.x - m_ptHotspot.x, point.y - m_ptHotspot.y );
		ClientToScreen( rect );

		switch ( m_Resize )
		{
		case NONE:
			rect.OffsetRect( size );
			break;
		case HORZ:
			rect.InflateRect( size.cx, 0 );
			break;
		case VERT:
			rect.InflateRect( 0, size.cy );
			break;
		}
		rect.NormalizeRect();

		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DRAG,
			(WPARAM)&rect, NULL );
	}
	CStatic::OnMouseMove(nFlags, point);
}

void CMyPicture::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_bRunMode == TRUE)
	{
		CStatic::OnLButtonUp(nFlags, point);
	}
	else if ( m_bDragging == TRUE )
	{
		BOOL bSuccess = GetParent()->SendMessage(
			WM_APP_CONTROL_DROP,
			(WPARAM)FALSE, (LPARAM)this );

		::ClipCursor( NULL );
		ReleaseCapture();
		::SetCursor( ::LoadCursor(NULL, IDC_ARROW) );

		m_bDragging = FALSE;
	}
	CStatic::OnLButtonUp(nFlags, point);
}

void CMyPicture::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	if ( m_bRunMode == TRUE )
		return;
		
	CMenu menu;
	menu.LoadMenu( IDR_MENU_CONTROL );
	CMenu *pMenu = menu.GetSubMenu( 0 );

	::SetWindowLongPtr(GetParent()->GetSafeHwnd(),
		GWLP_USERDATA, (LONG_PTR)this);
	pMenu->TrackPopupMenu( TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		point.x, point.y, GetParent() );
}

void CMyPicture::ReflectPropery()
{
	if ( m_iAction == 0 )
	{
		ModifyStyle( SS_ENHMETAFILE, SS_BITMAP );
		if ( m_strPath.IsEmpty() == TRUE )
		{
			SetBitmap( m_bitmapDefault );
		}
		else
		{
			if ( m_pBitmap )
			{
				delete m_pBitmap;
				m_pBitmap = NULL;
			}
			m_pBitmap = new CBitmap;
			if ( ::LoadBMPImage(m_strPath, *m_pBitmap, NULL) == TRUE )
			{
				SetBitmap( *m_pBitmap );
				BITMAP bm;
				m_pBitmap->GetBitmap( &bm );
				SetWindowPos( NULL, NULL, NULL, bm.bmWidth, bm.bmHeight,
					SWP_NOMOVE| SWP_NOZORDER | SWP_SHOWWINDOW );
			}
		}
	}
	else
	{
		ModifyStyle( SS_BITMAP, SS_ENHMETAFILE );
		SetEnhMetaFile( ::GetEnhMetaFile(m_strPath) );
	}
}
