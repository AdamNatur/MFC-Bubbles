
// Bubbles_FIXView.cpp: реализация класса CBubblesFIXView
//

#include "pch.h"
#include "framework.h"
#include <ctime>
#include <cmath>
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Bubbles_FIX.h"
#endif

#include "Bubbles_FIXDoc.h"
#include "Bubbles_FIXView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBubblesFIXView

IMPLEMENT_DYNCREATE(CBubblesFIXView, CView)

BEGIN_MESSAGE_MAP(CBubblesFIXView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_TIMER()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Создание или уничтожение CBubblesFIXView

CBubblesFIXView::CBubblesFIXView() noexcept
{
	// TODO: добавьте код создания

}

CBubblesFIXView::~CBubblesFIXView()
{
}

BOOL CBubblesFIXView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CBubblesFIXView

void CBubblesFIXView::OnDraw(CDC* pDC)
{
	CBubblesFIXDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->ChangeStyle();

		CPen pen(PS_SOLID, pDoc->W, RGB(pDoc->R, pDoc->G, pDoc->B));
		CPen* pOldPen = (CPen*)pDC->SelectObject(&pen);
		for (int i = 0; i < 5; i++) {
			pDoc->m_circ[i].Draw(pDC);
		}
	// TODO: добавьте здесь код отрисовки для собственных данных
}


// Печать CBubblesFIXView

BOOL CBubblesFIXView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CBubblesFIXView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CBubblesFIXView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}

// Диагностика CBubblesFIXView

#ifdef _DEBUG
void CBubblesFIXView::AssertValid() const
{
	CView::AssertValid();
}

void CBubblesFIXView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBubblesFIXDoc* CBubblesFIXView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBubblesFIXDoc)));
	return (CBubblesFIXDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CBubblesFIXView

void CBubblesFIXView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CBubblesFIXDoc* pDoc = GetDocument();

	CRect rect;
	GetClientRect(rect);

	for (int i = 0; i < 5; i++)
	{
		pDoc->m_circ[i].initYourBalls(rect.Width(), rect.Height());
	}

	SetTimer(0, 10, NULL);


	// TODO: добавьте специализированный код или вызов базового класса
}

void CBubblesFIXView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного


	CBubblesFIXDoc* pDoc = GetDocument();

	int x, y, r, k_switch, dim = 0;


	int i = 0;


	CRect rect;
	GetClientRect(rect);


	for (int i = 0; i < 5; i++) {
		pDoc->m_circ[i].CheckImpact(rect.Width(), rect.Height(), pDoc->m_circ, 5);
		pDoc->m_circ[i].m_iX += pDoc->m_circ[i].m_iA;
		pDoc->m_circ[i].m_iY += pDoc->m_circ[i].m_iB;
	}


	Invalidate();

	//CView::OnTimer(nIDEvent);
}


void CBubblesFIXView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CBubblesFIXDoc* pDoc = GetDocument();

	CMenu MainMenu;
	MainMenu.LoadMenuW(IDR_MAINFRAME);

	CMenu* SubMenu = MainMenu.GetSubMenu(4);

	if (pDoc->m_bVisible) {
		SubMenu->CheckMenuItem(ID_STYLE_VISIBLE, MF_CHECKED);
	}

	ClientToScreen(&point);

	SubMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CView::OnRButtonUp(nFlags, point);
}
