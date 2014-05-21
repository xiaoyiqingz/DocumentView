#pragma once



// CConfigView form view

class CConfigView : public CFormView
{
	DECLARE_DYNCREATE(CConfigView)

public:
	CConfigView();           // protected constructor used by dynamic creation
	virtual ~CConfigView();

public:
	enum { IDD = IDD_CONFIGVIEW };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};


