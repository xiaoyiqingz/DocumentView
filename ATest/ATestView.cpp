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

// ATestView.cpp : implementation of the CATestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ATest.h"
#endif

#include "ATestDoc.h"
#include "ATestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CATestView

IMPLEMENT_DYNCREATE(CATestView, CView)

BEGIN_MESSAGE_MAP(CATestView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CATestView construction/destruction

CATestView::CATestView()
{
	// TODO: add construction code here

}

CATestView::~CATestView()
{
}

BOOL CATestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CATestView drawing

void CATestView::OnDraw(CDC* /*pDC*/)
{
	CATestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CATestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CATestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CATestView diagnostics

#ifdef _DEBUG
void CATestView::AssertValid() const
{
	CView::AssertValid();
}

void CATestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CATestDoc* CATestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CATestDoc)));
	return (CATestDoc*)m_pDocument;
}
#endif //_DEBUG


// CATestView message handlers
