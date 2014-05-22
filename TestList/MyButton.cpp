// MyButton.cpp : implementation file
//

#include "stdafx.h"
#include "TestList.h"
#include "MyButton.h"
#include "SyncDir.h"


// CMyButton

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton()
{
	m_bkColor=0xFFFFFF;  
	m_textColor=0x000000;
}

CMyButton::~CMyButton()
{
}


BEGIN_MESSAGE_MAP(CMyButton, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_ENABLE()
END_MESSAGE_MAP()


// CMyButton message handlers


void CMyButton::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)  
	{  
		m_bOver = TRUE;  
		TRACKMOUSEEVENT tme;  
		tme.cbSize = sizeof(tme);  
		tme.hwndTrack = m_hWnd;  
		tme.dwFlags = TME_LEAVE | TME_HOVER;  
		tme.dwHoverTime = 50;  
		m_bTracking = (bool)_TrackMouseEvent(&tme);  
	}
	CButton::OnMouseMove(nFlags, point);
}


void CMyButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default

	m_bOver = FALSE;  
	m_bTracking = FALSE;  
	m_bDown=FALSE;  
	InvalidateRect(NULL, FALSE);

	CButton::OnMouseLeave();
}


void CMyButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bOver = TRUE;  
	InvalidateRect(NULL);

	CButton::OnMouseHover(nFlags, point);
}


void CMyButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	 m_bDown=TRUE; 

	CButton::OnLButtonDown(nFlags, point);
}


void CMyButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	m_bDown=FALSE;  

	CButton::OnLButtonUp(nFlags, point);
}

void CMyButton::SetBkColor(COLORREF color)
{
	m_bkColor = color;
}

void CMyButton::SetTextColor(COLORREF color)
{
	m_textColor = color;
}


BOOL CMyButton::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bRect = CButton::PreCreateWindow(cs);
	ButtonInit();
	return bRect;
}


void CMyButton::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CButton::PreSubclassWindow();
	ButtonInit();
}

void CMyButton::ButtonInit()
{
	m_bTracking = false;
	m_bDown = m_bOver = m_bDisable = false;
	m_bDisable = ::IsWindowEnabled(m_hWnd)?FALSE:TRUE;
//	ModifyStyle(NULL, BS_OWNERDRAW);
}


void CMyButton::DrawButton()
{
	HDC hdc = ::GetDC(m_hWnd);
	DrawButton(hdc);
	::ReleaseDC(m_hWnd, hdc);
}

void CMyButton::DrawButton(HDC hDestDC)
{
	CRect rc;  
	GetClientRect(rc);  
	int nWindth=rc.Width();  
	int nHeight=rc.Height();  
	HDC hDC=CreateCompatibleDC(hDestDC);
	HDC hMaskDC=CreateCompatibleDC(hDestDC);  
	HBITMAP hBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);  
	HBITMAP hMaskBitmap=CreateCompatibleBitmap(hDestDC,nWindth,nHeight);  
	HBITMAP hOldBitmap=(HBITMAP)SelectObject(hDC,hBitmap);  
	HBITMAP hOldMaskBitmap=(HBITMAP)SelectObject(hMaskDC,hMaskBitmap);  
	SetBkMode(hDC,TRANSPARENT);  

	CSyncDir* pParent=(CSyncDir*)GetParent();  
	CPoint pt(0,0);  
	MapWindowPoints(pParent,&pt,1);  
	pParent->m_bkImage.BitBlt(hDC,rc,pt,SRCCOPY);  



	int nAlpha=100;
	int nOffset=0;  

	HBRUSH hbr=CreateSolidBrush(m_bkColor);  
	FillRect(hMaskDC,&rc,hbr);  
	DeleteObject(hbr);  

	if(m_bDisable){  
		nAlpha=100;  
	}else if(m_bDown){  
		nAlpha=180;  
		nOffset=1;  
	}else if(m_bOver){  
		nAlpha=150;  
	}else{  
		nAlpha=100;  
	}  
	BLENDFUNCTION blend;  
	memset( &blend, 0, sizeof( blend) );  
	blend.BlendOp= AC_SRC_OVER;  
	blend.SourceConstantAlpha= nAlpha; 

	HRGN hRgn=CreateRoundRectRgn(0,0,nWindth,nHeight,3,3);  
	SelectClipRgn (hDC,hRgn);  
	AlphaBlend (hDC,0,0,nWindth,nHeight,hMaskDC, 0,0,nWindth,nHeight,blend);  

	CString strText;  
	GetWindowText(strText);  
	if(strText!=_T("")){  
		rc.InflateRect(-2,-2);  
		rc.OffsetRect(nOffset,nOffset);  
		HFONT hFont=(HFONT)SendMessage(WM_GETFONT);  
		if(!hFont)hFont=(HFONT)GetStockObject(DEFAULT_GUI_FONT);  
		HFONT hOldFont=(HFONT)SelectObject(hDC,hFont);  
		::SetTextColor(hDC,m_textColor);  
		::DrawText(hDC,strText,-1,&rc,DT_SINGLELINE|DT_CENTER|DT_VCENTER|DT_WORD_ELLIPSIS);  
		::SelectObject(hDC,hOldFont);  
	}  
	SelectClipRgn (hDC,NULL);  
	DeleteObject(hRgn);  

	BitBlt(hDestDC,0,0,nWindth,nHeight,hDC,0,0,SRCCOPY);  

	SelectObject(hDC,hOldBitmap);  
	DeleteObject(hBitmap);  
	DeleteDC(hDC);  
	SelectObject(hMaskDC,hOldMaskBitmap);  
	DeleteObject(hMaskBitmap);  
	DeleteDC(hMaskDC);  
}

void CMyButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{

	// TODO:  Add your code to draw the specified item
	DrawButton(lpDrawItemStruct->hDC);
}


void CMyButton::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);

	// TODO: Add your message handler code here
	m_bDisable=IsWindowEnabled()?FALSE:TRUE;  
	DrawButton();
}
