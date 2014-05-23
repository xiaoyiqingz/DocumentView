#pragma once
#include "Util.h"

// CDir view

class CDir : public CTreeView
{
	DECLARE_DYNCREATE(CDir)

public:
	CDir();           // protected constructor used by dynamic creation
	virtual ~CDir();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();

	CImageList m_ImageList;
	CMyImageList m_myImageList;

	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


