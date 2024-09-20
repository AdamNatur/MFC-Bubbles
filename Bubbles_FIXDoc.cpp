
// Bubbles_FIXDoc.cpp: реализация класса CBubblesFIXDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Bubbles_FIX.h"
#endif

#include "Bubbles_FIXDoc.h"
#include "MainFrm.h"
#include <propkey.h>
#include <cmath>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include "Bubbles_FIXView.h"
#include "CMyTreeView.h"

IMPLEMENT_DYNCREATE(CBubblesFIXDoc, CDocument)

BEGIN_MESSAGE_MAP(CBubblesFIXDoc, CDocument)

	ON_COMMAND(ID_STYLE_COLOR_BLUE, &CBubblesFIXDoc::OnStyleColorBlue)
	ON_COMMAND(ID_STYLE_COLOR_GREEN, &CBubblesFIXDoc::OnStyleColorGreen)
	ON_COMMAND(ID_STYLE_COLOR_RED, &CBubblesFIXDoc::OnStyleColorRed)
	ON_COMMAND(ID_STYLE_THICKNESS_3PX, &CBubblesFIXDoc::OnStyleThickness3px)
	ON_COMMAND(ID_STYLE_THICKNESS_6PX, &CBubblesFIXDoc::OnStyleThickness6px)
	ON_COMMAND(ID_STYLE_THICKNESS_9PX, &CBubblesFIXDoc::OnStyleThickness9px)
	ON_COMMAND(ID_STYLE_VISIBLE, &CBubblesFIXDoc::OnStyleVisible)
	ON_UPDATE_COMMAND_UI(ID_STYLE_VISIBLE, &CBubblesFIXDoc::OnUpdateStyleVisible)
END_MESSAGE_MAP()


// Создание или уничтожение CBubblesFIXDoc


int GetRandomNumber(int min, int max)
{
	// Установить генератор случайных чисел
	//srand(time(NULL));

	// Получить случайное число - формула
	int num = min + rand() % (max - min + 1);

	return num;
}

CMyCircle::CMyCircle()
{
	m_iX = 100;
	m_iY = 200;
	m_iR = 50;
	m_iA = m_iR;
	m_iB = m_iR;
}

CMyCircle::CMyCircle(int x, int y, int r, int a, int b)
{
	m_iX = x;
	m_iY = y;
	m_iR = r;
	m_iA = a;
	m_iB = b;
}

void CMyCircle::initYourBalls(int w, int h) {
	m_iR = GetRandomNumber(25, 50);
	m_iX = GetRandomNumber(m_iR, w - m_iR);
	m_iY = GetRandomNumber(m_iR, h - m_iR);

	m_iA = GetRandomNumber(-5, 5);
	m_iB = GetRandomNumber(-5, 5);

	while (m_iA == 0 || m_iB == 0) {
		m_iA = GetRandomNumber(-5, 5);
		m_iB = GetRandomNumber(-5, 5);
	}
}

void CMyCircle::Draw(CDC* pDC)
{

	pDC->MoveTo(m_iX + m_iR, m_iY);
	pDC->AngleArc(m_iX, m_iY, m_iR, 0, 360);
}

void CMyCircle::CheckImpact(int bound_x, int bound_y, CMyCircle* m_circ, int size)
{

	if (m_iY <= m_iR)
	{
		m_iA = (1 + rand() % 10) * (-1 + rand() % 1);
		m_iB = (1 + rand() % 10);
	}
	else if (bound_y - m_iR <= m_iY)
	{
		m_iA = (1 + rand() % 10) * (-1 + rand() % 1);
		m_iB = (1 + rand() % 10) * (-1);
	}
	else if (m_iX <= m_iR) {
		m_iA = (1 + rand() % 10);
		m_iB = (1 + rand() % 10) * (-1 + rand() % 1);
	}
	else if (bound_x - m_iR <= m_iX)
	{
		m_iA = (1 + rand() % 10) * (-1);
		m_iB = (1 + rand() % 10) * (-1 + rand() % 1);
	}


	for (int n = 0; n < 5; n++)
	{
		double dim = sqrt(pow(m_iX - m_circ[n].m_iX, 2) + pow(m_iY - m_circ[n].m_iY, 2));
		if (dim <= m_iR + m_circ[n].m_iR && dim != 0)
		{
			int k_switch = m_circ[n].m_iA;
			m_circ[n].m_iA = -1 * m_circ[n].m_iB;
			m_circ[n].m_iB = k_switch;
			k_switch = m_iA;
			m_iA = -1 * m_iB;
			m_iB = k_switch;
		}
	}
}

CBubblesFIXDoc::CBubblesFIXDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CBubblesFIXDoc::~CBubblesFIXDoc()
{
}

void CBubblesFIXDoc::ChangeStyle() {
	R = 0;
	G = 0;
	B = 0;

	if (m_bRed) {
		R = 255;
	}
	else if (m_bGreen) {
		G = 255;
	}
	else if (m_bBlue) {
		B = 255;
	}
	else if (m_bVisible) {
		R = 255;
		G = 255;
		B = 255;
	}


	if (m_bBold) {
		W = 9;
	}
	else if (m_bPlump) {
		W = 6;
	}
	else if (m_bThin) {
		W = 3;
	}
	else {
		W = 1;
	}

}

BOOL CBubblesFIXDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	CWnd* MainWnd = AfxGetMainWnd();

	if (MainWnd)
	{

		m_pTreeView = (CMyTreeView*)((CMainFrame*)MainWnd)->m_wndSplitter.GetPane(0, 0);

	}

	m_bRed = m_bBlue = m_bGreen = m_bVisible = false;
	m_bBold = m_bPlump = m_bThin = false;

	m_pTreeView->FillTree();


	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// Сериализация CBubblesFIXDoc

void CBubblesFIXDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CBubblesFIXDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CBubblesFIXDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CBubblesFIXDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CBubblesFIXDoc

#ifdef _DEBUG
void CBubblesFIXDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBubblesFIXDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CBubblesFIXDoc




void CBubblesFIXDoc::OnStyleColorBlue()
{
	// TODO: добавьте свой код обработчика команд
	m_bBlue = true;
	m_bRed = false;
	m_bGreen = false;
}


void CBubblesFIXDoc::OnStyleColorGreen()
{
	// TODO: добавьте свой код обработчика команд
	m_bBlue = false;
	m_bRed = false;
	m_bGreen = true;
}


void CBubblesFIXDoc::OnStyleColorRed()
{
	// TODO: добавьте свой код обработчика команд
	m_bBlue = false;
	m_bRed = true;
	m_bGreen = false;
}


void CBubblesFIXDoc::OnStyleThickness3px()
{
	// TODO: добавьте свой код обработчика команд
	m_bBold = false;
	m_bPlump = false;
	m_bThin = true;
}


void CBubblesFIXDoc::OnStyleThickness6px()
{
	// TODO: добавьте свой код обработчика команд
	m_bBold = false;
	m_bPlump = true;
	m_bThin = false;
}


void CBubblesFIXDoc::OnStyleThickness9px()
{
	// TODO: добавьте свой код обработчика команд
	m_bBold = true;
	m_bPlump = false;
	m_bThin = false;
}


void CBubblesFIXDoc::OnUpdateStyleVisible(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bVisible);
}

void CBubblesFIXDoc::OnStyleVisible()
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	m_bVisible = !m_bVisible;
}


