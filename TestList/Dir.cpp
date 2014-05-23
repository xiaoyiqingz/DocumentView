// Dir.cpp : implementation file
//

#include "stdafx.h"
#include "TestList.h"
#include "Dir.h"


// CDir

IMPLEMENT_DYNCREATE(CDir, CTreeView)

CDir::CDir()
{

}

CDir::~CDir()
{
}

BEGIN_MESSAGE_MAP(CDir, CTreeView)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, &CDir::OnTvnSelchanged)
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CDir diagnostics

#ifdef _DEBUG
void CDir::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CDir::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CDir message handlers


void CDir::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CTreeCtrl &dirTree = GetTreeCtrl();

	TV_ITEM tvi;
	HTREEITEM temp_hItem;
	TV_INSERTSTRUCT tvis;

/*
	SHFILEINFO sfi;
	HIMAGELIST sys_small_icon;
	sys_small_icon = (HIMAGELIST) SHGetFileInfo(NULL, 0, &sfi, sizeof(sfi),
		SHGFI_SYSICONINDEX | SHGFI_SMALLICON);
	CImageList m_Image;
	m_Image.Attach(sys_small_icon);*/

	dirTree.SetImageList(m_myImageList.GetMyImageList(), TVSIL_NORMAL);
//	m_Image.Detach();

	tvi.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_CHILDREN;
	
	tvi.pszText = _T("root");
	tvi.iImage = 1;
	tvi.iSelectedImage = 1;

	tvis.item = tvi;
	tvis.hParent = TVI_ROOT;
	HTREEITEM hParent = dirTree.InsertItem(&tvis);

	for (int i = 1; i < 3; i++) {
		CString str(_T("child"));
		str.AppendFormat(_T("%d"), i);
		USES_CONVERSION;   
		tvi.pszText = new wchar_t[str.GetLength()+1];
		tvi.iImage = i % 3;
		tvi.iSelectedImage = (i + 1) % 3;
		wcscpy(tvi.pszText, str);
		tvis.item = tvi;
		tvis.hParent = hParent;
		temp_hItem = dirTree.InsertItem(&tvis);
	}

	for (int i = 21; i < 25; i++) {
		CString str(_T("child"));
		str.AppendFormat(_T("%d"), i);
		USES_CONVERSION;   
		tvi.pszText = new wchar_t[str.GetLength()+1];
		tvi.iImage = i % 3;
		tvi.iSelectedImage = (i + 1) % 3;
		wcscpy(tvi.pszText, str);
		tvis.item = tvi;
		tvis.hParent = temp_hItem;
		dirTree.InsertItem(&tvis);
	}

}


BOOL CDir::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES | TVS_LINESATROOT;

	return CTreeView::PreCreateWindow(cs);
}


void CDir::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
/*
	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	TV_ITEM item;
	item.hItem = hItem;
	item.mask = TVIF_TEXT;
	CString str;
	int nLen = 128;
	int nRes;

	do {
		nLen *=2;
		item.pszText = str.GetBufferSetLength(nLen);
		item.cchTextMax = nLen;
		::SendMessage(pNMTreeView->hdr.hwndFrom, TVM_GETITEM, 0, (LPARAM)&item);
		nRes = lstrlen(item.pszText);
	} while (nRes == nLen-1);
	MessageBox(str);
	str.ReleaseBuffer();*/

	*pResult = 0;
}


BOOL CDir::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
/*   ±³¾°É«½¥±ä
	CRect rc; 
	GetClientRect(&rc); 
	for(int i=1;i<=rc.Height();i++)
	{ 
		float a=(float)(255.0/(float)rc.Height())*i; 
		pDC->FillSolidRect(0,i-1,rc.Width(),i,RGB(255-a,255-a,255)); 
	}
	return TRUE;
*/	
	return CTreeView::OnEraseBkgnd(pDC);
}
