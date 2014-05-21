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

// DTestView.cpp : implementation of the CDTestView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DTest.h"
#endif

#include "DTestDoc.h"
#include "DTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDTestView

IMPLEMENT_DYNCREATE(CDTestView, CView)

BEGIN_MESSAGE_MAP(CDTestView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDTestView construction/destruction

CDTestView::CDTestView()
{
	// TODO: add construction code here

}

CDTestView::~CDTestView()
{
}

BOOL CDTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDTestView drawing

void CDTestView::OnDraw(CDC* /*pDC*/)
{
	CDTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CDTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDTestView diagnostics

#ifdef _DEBUG
void CDTestView::AssertValid() const
{
	CView::AssertValid();
}

void CDTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDTestDoc* CDTestView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDTestDoc)));
	return (CDTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CDTestView message handlers
