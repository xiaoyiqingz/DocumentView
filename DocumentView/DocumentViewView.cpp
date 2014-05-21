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

// DocumentViewView.cpp : implementation of the CDocumentViewView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DocumentView.h"
#endif

#include "DocumentViewDoc.h"
#include "DocumentViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDocumentViewView

IMPLEMENT_DYNCREATE(CDocumentViewView, CView)

BEGIN_MESSAGE_MAP(CDocumentViewView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CDocumentViewView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
//	ON_WM_PAINT()
END_MESSAGE_MAP()

// CDocumentViewView construction/destruction

CDocumentViewView::CDocumentViewView()
{
	// TODO: add construction code here
	CreateImageList();	
}

CDocumentViewView::~CDocumentViewView()
{
}

BOOL CDocumentViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDocumentViewView drawing

void CDocumentViewView::OnDraw(CDC* /*pDC*/)
{
	CDocumentViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
//	CreateDeviceList();
// 	CClientDC dc(this);
// 	CString str("nihao");

/*
	CPen pen(PS_SOLID, 2, RGB(0,255,0));
	CPen* oldPen = dc.SelectObject(&pen);*/

// 	dc.SetTextColor(RGB(0,125,125));
// 	dc.TextOut(20, 20, str);

	// TODO: add draw code for native data here
}


// CDocumentViewView message handlers



/*
void CDocumentViewView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
	CString str("hello");
	dc.TextOut(40, 40, str);
	OnDraw(&dc);
}*/

// CDocumentViewView printing


void CDocumentViewView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CDocumentViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDocumentViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDocumentViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CDocumentViewView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDocumentViewView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDocumentViewView diagnostics

#ifdef _DEBUG
void CDocumentViewView::AssertValid() const
{
	CView::AssertValid();
}

void CDocumentViewView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDocumentViewDoc* CDocumentViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDocumentViewDoc)));
	return (CDocumentViewDoc*)m_pDocument;
}
#endif //_DEBUG


BOOL CDocumentViewView::CreateDeviceList()
{
	
	CRect rect;
	GetWindowRect(rect);
	ScreenToClient(rect);
//	HWND hWnd = GetSafeHwnd();
//	CWnd *pWnd = CWnd::FromHandle(hWnd);
//	m_ListCtrlDevice.DeleteAllItems();
	m_ListCtrlDevice.Create(WS_CHILD|WS_VISIBLE|WS_BORDER|LVS_ICON, 
		rect, this, IDL_DEVICE);

	m_ListCtrlDevice.SetImageList(&m_ImageList, LVSIL_NORMAL);
	m_ListCtrlDevice.SetImageList(&m_ImageList, LVSIL_SMALL);
	m_ListCtrlDevice.InsertColumn(0, _T("设备名称"));
	m_ListCtrlDevice.InsertColumn(1, _T("设备地址"), LVCFMT_LEFT);
//	m_ListCtrlDevice.SetColumnWidth(0, 120);
//	m_ListCtrlDevice.SetColumnWidth(1, 460);

	DWORD ExStyle=m_ListCtrlDevice.GetExtendedStyle();
	ExStyle |= LVS_EX_FULLROWSELECT;
	ExStyle |= LVS_EX_GRIDLINES;
	ExStyle |= LVS_EX_SUBITEMIMAGES;   //must!
	// ExStyle |= LVS_EX_CHECKBOXES;
	m_ListCtrlDevice.SetExtendedStyle(ExStyle);

	for (int i = 0; i < 100; i++) {
		m_ListCtrlDevice.InsertItem(i, _T("name"), i % 3);
		m_ListCtrlDevice.SetItemText(i , 1, _T("path"));
	}
	m_ListCtrlDevice.SetColumnWidth(0, LVSCW_AUTOSIZE);
	m_ListCtrlDevice.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	return TRUE;
}


void CDocumentViewView::CreateImageList()
{
	m_ImageList.Create(64,64, ILC_COLOR32 |ILC_MASK , 15, 1);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_ANDROID));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_IOS));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_WINDOWS));
}

void CDocumentViewView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CreateDeviceList();
}


void CDocumentViewView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
}
