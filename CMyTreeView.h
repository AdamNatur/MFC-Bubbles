#pragma once

#include "afxcview.h"

class CBubblesFIXDoc;
// Просмотр CMyTreeView

class CMyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CMyTreeView)

protected:
	CMyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~CMyTreeView();


public:
	void FillTree();
	HTREEITEM m_hThickRoot, m_hBold, m_hPlump, m_hThin;
	HTREEITEM m_hColorRoot, m_hGreen, m_hRed, m_hBlue;
	CBubblesFIXDoc* m_pDoc;
	CBubblesFIXDoc* m_pView;
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};



