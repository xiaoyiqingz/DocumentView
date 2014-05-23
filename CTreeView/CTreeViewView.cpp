// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// http://msdn.microsoft.com/officeui.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// CTreeViewView.cpp : implementation of the CCTreeViewView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CTreeView.h"
#endif

#include "CTreeViewDoc.h"
#include "CTreeViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCTreeViewView

IMPLEMENT_DYNCREATE(CCTreeViewView, CTreeView)

BEGIN_MESSAGE_MAP(CCTreeViewView, CTreeView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CCTreeViewView construction/destruction

CCTreeViewView::CCTreeViewView()
{
	// TODO: add construction code here

}

CCTreeViewView::~CCTreeViewView()
{
}

BOOL CCTreeViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

void CCTreeViewView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

}

void CCTreeViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CCTreeViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CCTreeViewView diagnostics

#ifdef _DEBUG
void CCTreeViewView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CCTreeViewView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CCTreeViewDoc* CCTreeViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCTreeViewDoc)));
	return (CCTreeViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CCTreeViewView message handlers


BOOL CCTreeViewView::OnEraseBkgnd(CDC* pDC)
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
