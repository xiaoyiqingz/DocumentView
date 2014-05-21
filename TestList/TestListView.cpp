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

// TestListView.cpp : implementation of the CTestListView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TestList.h"
#endif

#include "TestListDoc.h"
#include "TestListView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestListView

IMPLEMENT_DYNCREATE(CTestListView, CListView)

BEGIN_MESSAGE_MAP(CTestListView, CListView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDB_MYBUTTON, CTestListView::OnMyButtonClick)
	ON_MESSAGE(WM_MY_USERMESSAGE, UpdateDevice)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_SIZE()
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, &CTestListView::OnLvnBegindrag)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CTestListView construction/destruction

CTestListView::CTestListView()
{
	// TODO: add construction code here
		CreateImageList();
		m_bDragging = FALSE;
}

CTestListView::~CTestListView()
{
}

BOOL CTestListView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs


	return CListView::PreCreateWindow(cs);
}

void CTestListView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestListView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


void CTestListView::CreateImageList()
{
	m_ImageList.Create(64,64, ILC_COLOR32 |ILC_MASK , 15, 1);
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_ANDROID));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_IOS));
	m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_DEVICE_TYPE_WINDOWS));
}

// CTestListView diagnostics

#ifdef _DEBUG
void CTestListView::AssertValid() const
{
	CListView::AssertValid();
}

void CTestListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTestListDoc* CTestListView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestListDoc)));
	return (CTestListDoc*)m_pDocument;
}

#endif //_DEBUG


// CTestListView message handlers




void CTestListView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: Add your specialized code here and/or call the base class
	CTestListDoc* pTestDoc = GetDocument();
	ASSERT_VALID(pTestDoc);
}


void CTestListView::OnMyButtonClick()
{
	SendMessage(WM_MY_USERMESSAGE);
}

LRESULT CTestListView::UpdateDevice(WPARAM wParam, LPARAM lParam)
{
	CListCtrl &deviceList = GetListCtrl();

	CRect rectnew;
	GetClientRect(&rectnew);
//	ScreenToClient(&rectnew);
	CPoint pointcenter, pointrect;

	//0	
	pointcenter.x = (rectnew.right + rectnew.left) / 2;
	pointcenter.y = (rectnew.bottom + rectnew.top) / 2;
	deviceList.SetItemPosition(0, pointcenter);
	
	//1
	pointrect.x = pointcenter.x - 141;
	pointrect.y = pointcenter.y - 141;
	deviceList.SetItemPosition(1, pointrect);

	//2
	pointrect.x = pointcenter.x + 141;
	pointrect.y = pointcenter.y - 141;
	deviceList.SetItemPosition(2, pointrect);

	//3
	pointrect.x = pointcenter.x - 141;
	pointrect.y = pointcenter.y + 141;
	deviceList.SetItemPosition(3, pointrect);

	//4
	pointrect.x = pointcenter.x + 141;
	pointrect.y = pointcenter.y + 141;
	deviceList.SetItemPosition(4, pointrect);

	CRect rect;
	GetClientRect(&rect);
//	ScreenToClient(&rect);
	rect.left = rect.right-50;
	rect.right = rect.right - 10;
	rect.top = rect.bottom - 50;
	rect.bottom = rect.bottom - 10;

	
	CWnd* pWnd = GetDlgItem(IDB_MYBUTTON);
	pWnd->MoveWindow(rect);

	CClientDC dc(this);
	CPen penOnLine(PS_SOLID, 1, RGB(255,0,0));
	CPen penOffLine(PS_DASH, 1, RGB(255,0,0));

	CRect rectl;
	deviceList.GetItemRect(1, &rectl, LVIR_BOUNDS);
	CPen *penOld = dc.SelectObject(&penOnLine);
	CPoint pointl;
	pointl.x = rectl.right;
	pointl.y = rectl.bottom;
	dc.MoveTo(pointl);

	deviceList.GetItemRect(0, &rectl, LVIR_BOUNDS);
	pointl.x = rectl.left;
	pointl.y = rectl.top;
	dc.LineTo(pointl);
 	
	deviceList.GetItemRect(2, &rectl, LVIR_BOUNDS);
	pointl.x = rectl.left;
	pointl.y = rectl.bottom;
	dc.SelectObject(&penOffLine);
 	dc.MoveTo(pointl);

	deviceList.GetItemRect(0, &rectl, LVIR_BOUNDS);
	pointl.x = rectl.right;
	pointl.y = rectl.top;
 	dc.LineTo(pointl);
	
	return 0;
}


void CTestListView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CListCtrl &deviceList = GetListCtrl();
	POSITION pos = deviceList.GetFirstSelectedItemPosition();
	int item = deviceList.GetNextSelectedItem(pos);

	CString strName;
	strName= deviceList.GetItemText(item, 0);
	CString str;
	str.Format(_T("±àºÅ£º%d\nÃû³Æ£º%s"), item, strName);

	MessageBox(str);
	CListView::OnLButtonDblClk(nFlags, point);
}



void CTestListView::OnInitialUpdate()
{
	CListView::OnInitialUpdate();


	// TODO: You may populate your ListView with items by directly accessing
	//  its list control through a call to GetListCtrl().
 	CListCtrl &deviceList = GetListCtrl();
 
	COLORREF color(RGB(0,255,255));
 	deviceList.SetImageList(&m_ImageList, LVSIL_NORMAL);
 	deviceList.SetTextColor(color);


	CPoint point(30, 30);
//	ScreenToClient(&point);
 	for (int i = 0; i < 5; i++) {
 		CString str(_T("name"));
		point.x = point.x + 200;
		point.y = point.y + 200;
 		str.AppendFormat(_T("%d"), i);
 		deviceList.InsertItem(i, str, i % 3);
		deviceList.SetItemPosition(i, point);
 	}
 	
 	CRect rect_button, rect;
 	CString str(_T("¸üÐÂ"));
	
 	GetClientRect(&rect);
 	ScreenToClient(&rect);
 	rect_button.bottom = rect.bottom;
 	rect_button.right = rect.right;
 	rect_button.left = rect.right -30;
 	rect_button.top = rect.bottom - 30;
 
 	m_btUpdate.Create(str, WS_CHILD | WS_VISIBLE | BS_USERBUTTON , rect_button, 
 		this, IDB_MYBUTTON);
}

void CTestListView::OnSize(UINT nType, int cx, int cy)
{
	CListView::OnSize(nType, cx, cy);

	CListCtrl& deviceList = GetListCtrl();
	CRect  win, client;
	CString strWin, strClient;
	GetWindowRect(&win);
	GetClientRect(&client);
	

	strWin.Format(_T("win: left:%d, rigih:%d, top:%d, botton:%d\n"),
		win.left, win.right, win.top, win.bottom);
	strClient.Format(_T("Client: left:%d, rigih:%d, top:%d, botton:%d\n"),
		client.left, client.right, client.top, client.bottom);
	OutputDebugString(strWin);
	OutputDebugString(strClient);
	//
	//deviceList.GetWindowRect(&win);
	//deviceList.GetClientRect(&client);
	//
	//strWin.Format(_T("device win: left:%d', rigih:%d, top:%d, botton:%d\n"),
	//	win.left, win.right, win.top, win.bottom);
	//strClient.Format(_T("device Client: left:%d, rigih:%d, top:%d, botton:%d\n"),
	//	client.left, client.right, client.top, client.bottom);
	//OutputDebugString(strWin);
	//OutputDebugString(strClient);
	//
	//::GetWindowRect(NULL, &win);
	//strWin.Format(_T("::win: left:%d, rigih:%d, top:%d, botton:%d\n"),
	//	win.left, win.right, win.top, win.bottom);
	//OutputDebugString(strWin);


	// TODO: Add your message handler code herem

	SetRedraw(FALSE);

	CRect rectnew;
	deviceList.GetClientRect(&rectnew);
//	ClientToScreen(rectnew);
	CPoint pointcenter, pointrect;

	CRect rectItem;
	deviceList.GetItemRect(0, &rectItem, LVIR_ICON);
	//0	
	pointcenter.x = (rectnew.right + rectnew.left - rectItem.Width()) / 2;
	pointcenter.y = (rectnew.bottom + rectnew.top - rectItem.Height()) / 2;
	//pointcenter.x = 0;
	//pointcenter.y = 0;
	deviceList.SetItemPosition(0, pointcenter); 

	CString str;
	str.Format(_T("point : x= %d, y =%d\n"), pointcenter.x, pointcenter.y);
	OutputDebugString(str);

	//1
	pointrect.x = pointcenter.x - 141;
	pointrect.y = pointcenter.y - 141;
	deviceList.SetItemPosition(1, pointrect);

	//2
	pointrect.x = pointcenter.x + 141;
	pointrect.y = pointcenter.y - 141;
	deviceList.SetItemPosition(2, pointrect);

	//3
	pointrect.x = pointcenter.x - 141;
	pointrect.y = pointcenter.y + 141;
	deviceList.SetItemPosition(3, pointrect);

	//4
	pointrect.x = pointcenter.x + 141;
	pointrect.y = pointcenter.y + 141;
	deviceList.SetItemPosition(4, pointrect);


	SetRedraw(TRUE);
	Invalidate();
	UpdateWindow();
}


void CTestListView::OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	CListCtrl & deviceList = GetListCtrl();
	m_nDragIndex = pNMLV->iItem;
	m_bDragging = TRUE;
	// pNMLV->ptAction
	CPoint ptItem;
	deviceList.GetOrigin(&m_ptOrigin);
	deviceList.GetItemPosition(m_nDragIndex, &ptItem);

	m_ptOffset = ptItem + m_ptOrigin - pNMLV->ptAction;


	// CString strWin;
	// strWin.Format(_T("::item: left:%d, rigih:%d, top:%d, botton:%d, ptAction.x:%d, ptAction.y:%d\n"),
	// 	win.left, win.right, win.top, win.bottom, pNMLV->ptAction.x, pNMLV->ptAction.y);
	// OutputDebugString(strWin);

	*pResult = 0;
}


void CTestListView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CRect Rect;
	CListCtrl &deviceList = GetListCtrl();
	MapWindowPoints(&deviceList, &point, 1);
	if (m_bDragging) 
	{
		// deviceList.GetItemRect(m_nDragIndex, &Rect, LVIR_ICON);
		// point -= CPoint(Rect.Width(), Rect.Height());
		CPoint ptItem = point - m_ptOrigin + m_ptOffset;
		deviceList.SetItemPosition(m_nDragIndex, ptItem);
	}	
	CListView::OnMouseMove(nFlags, point);

}


void CTestListView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CListCtrl& deviceList = GetListCtrl();
	if (m_bDragging) {
		// MapWindowPoints(&deviceList, &point, 1);
		CPoint ptItem = point - m_ptOrigin + m_ptOffset;
		deviceList.SetItemPosition(m_nDragIndex, ptItem);
		m_bDragging = FALSE;
	}	
	CListView::OnLButtonUp(nFlags, point);
}

