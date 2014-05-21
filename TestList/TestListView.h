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

// TestListView.h : interface of the CTestListView class
//

#pragma once
#define WM_MY_USERMESSAGE (WM_USER+30)

class CTestListView : public CListView
{
public: // create from serialization only
	CTestListView();
	DECLARE_DYNCREATE(CTestListView)

// Attributes
public:
	CTestListDoc* GetDocument() const;

	CImageList  m_ImageList;
	CButton     m_btUpdate;
	int         m_nDragIndex;
	BOOL		m_bDragging;
	CPoint      m_ptOffset;
	CPoint      m_ptOrigin;
	CRect       m_rViewRect;

	void CreateImageList();

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // called first time after construct

// Implementation
public:
	virtual ~CTestListView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMyButtonClick();
	afx_msg LRESULT UpdateDevice(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);	
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLvnBegindrag(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in TestListView.cpp
inline CTestListDoc* CTestListView::GetDocument() const
   { return reinterpret_cast<CTestListDoc*>(m_pDocument); }
#endif

