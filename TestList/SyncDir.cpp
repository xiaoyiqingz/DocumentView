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
	m_edit1 = _T("");
}

CSyncDir::~CSyncDir()
{
}

void CSyncDir::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
}

BEGIN_MESSAGE_MAP(CSyncDir, CFormView)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CSyncDir::OnClickedButton1)
	ON_WM_ERASEBKGND()
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
	
	switch (nCtlColor) {
		case CTLCOLOR_DLG:
		{
			pDC->SetBkMode(TRANSPARENT);
			HBRUSH br =(HBRUSH)CreateSolidBrush(RGB(255, 255, 255)); 
			return (HBRUSH) br ;
		}
		case CTLCOLOR_EDIT:
		{
			pDC->SetBkMode(TRANSPARENT);
			HBRUSH br = (HBRUSH)CreateSolidBrush(RGB(0,255,255));
			return (HBRUSH) br;
		}
		default:
			return CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	}	
}


void CSyncDir::OnClickedButton1()
{
	// TODO: Add your control notification handler code here
	UpdateData();
	MessageBox(m_edit1);
}



BOOL CSyncDir::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect rc; 
	GetClientRect(&rc); 
	for(int i=1;i<=rc.Height();i++)
	{ 
		float a=(float)(255.0/(float)rc.Height())*i; 
		pDC->FillSolidRect(0,i-1,rc.Width(),i,RGB(255-a,255-a,255)); 
	}
	return TRUE;
}
