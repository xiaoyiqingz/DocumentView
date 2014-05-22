#pragma once


// CSyncDir form view

class CSyncDir : public CFormView
{
	DECLARE_DYNCREATE(CSyncDir)

public:
	CSyncDir();           // protected constructor used by dynamic creation
	virtual ~CSyncDir();

public:
	enum { IDD = IDD_SYNCDIR };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedButton1();
	CString m_edit1;
	CImage  m_bkImage;
};


