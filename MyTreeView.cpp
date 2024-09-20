// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "Bubbles_FIX.h"
#include "CMyTreeView.h"


// CMyTreeView

IMPLEMENT_DYNCREATE(CMyTreeView, CTreeView)

CMyTreeView::CMyTreeView()
{

}

CMyTreeView::~CMyTreeView()
{
}

BEGIN_MESSAGE_MAP(CMyTreeView, CTreeView)
//	ON_WM_CREATE()
//ON_WM_CREATE()
ON_WM_CREATE()
ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CMyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	tree.DeleteAllItems();

	m_hThickRoot = tree.InsertItem(L"Толщина", -1, -1, NULL, TVI_FIRST);

	m_hBold = tree.InsertItem(L"9px", -1, -1, m_hThickRoot, TVI_FIRST);
	m_hPlump = tree.InsertItem(L"6px", -1, -1, m_hThickRoot, TVI_FIRST);
	m_hThin = tree.InsertItem(L"3px", -1, -1, m_hThickRoot, TVI_FIRST);

	m_hColorRoot = tree.InsertItem(L"Colors", -1, -1, NULL, TVI_FIRST);

	m_hRed = tree.InsertItem(L"Red", -1, -1, m_hColorRoot, TVI_FIRST);
	m_hBlue = tree.InsertItem(L"Green", -1, -1, m_hColorRoot, TVI_FIRST);
	m_hGreen = tree.InsertItem(L"Blue", -1, -1, m_hColorRoot, TVI_FIRST);

	tree.Expand(m_hColorRoot, TVE_EXPAND);
	tree.Expand(m_hThickRoot, TVE_EXPAND);
}



// Диагностика CMyTreeView

#ifdef _DEBUG
void CMyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG

// Обработчики сообщений CMyTreeView


