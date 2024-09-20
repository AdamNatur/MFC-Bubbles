#include "pch.h"
#include "CMyTreeView.h"


#include "Bubbles_FIXDoc.h"


int CMyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT |
		TVS_SHOWSELALWAYS | TVS_CHECKBOXES;
	
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void CMyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CTreeCtrl& tree = GetTreeCtrl();
	CTreeView::OnLButtonDown(nFlags, point);

	CRect rc;
	tree.GetItemRect(m_hColorRoot, &rc, false);
	m_pDoc->m_bRed = tree.GetCheck(m_hRed);
	m_pDoc->m_bBlue = tree.GetCheck(m_hGreen);
	m_pDoc->m_bGreen = tree.GetCheck(m_hBlue);
	tree.GetItemRect(m_hThickRoot, &rc, false);
	m_pDoc->m_bBold = tree.GetCheck(m_hBold);
	m_pDoc->m_bPlump = tree.GetCheck(m_hPlump);
	m_pDoc->m_bThin = tree.GetCheck(m_hThin);
}
