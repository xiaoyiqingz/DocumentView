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
