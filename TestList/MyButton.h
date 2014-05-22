#pragma once

// CMyButton

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton();
	virtual ~CMyButton();

	void SetBkColor(COLORREF color);  
	void SetTextColor(COLORREF color);

	bool m_bOver;  
	bool m_bDown;  
	bool m_bDisable;  
	bool m_bTracking;  
	COLORREF m_bkColor;  
	COLORREF m_textColor;

protected:
	DECLARE_MESSAGE_MAP()


public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void PreSubclassWindow();

	void ButtonInit();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void  DrawButton();
	void  DrawButton(HDC hDestDC);	
	afx_msg void OnEnable(BOOL bEnable);
};


