// SyncDir.cpp : implementation file
//

#include "stdafx.h"
#include "TestList.h"
#include "SyncDir.h"


// CSyncDir

IMPLEMENT_DYNCREATE(CSyncDir, CFormView)

CSyncDir::CSyncDir()
	: CFormView(CSyncDir::IDD)
{

}

CSyncDir::~CSyncDir()
{
}

void CSyncDir::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSyncDir, CFormView)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CSyncDir diagnostics

#ifdef _DEBUG
void CSyncDir::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSyncDir::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSyncDir message handlers



HBRUSH CSyncDir::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);

//	pDC->SetBkMode(TRANSPARENT);
	

	if (nCtlColor == CTLCOLOR_DLG)
	{
		pDC->SetBkMode(TRANSPARENT);
		HBRUSH br =(HBRUSH)CreateSolidBrush(RGB(0, 255, 0)); 
		return (HBRUSH) br ; 

	} else {
		return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	}
	
}
