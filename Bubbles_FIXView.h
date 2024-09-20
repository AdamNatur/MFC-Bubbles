
// Bubbles_FIXView.h: интерфейс класса CBubblesFIXView
//

#pragma once
#include "Bubbles_FIXDoc.h"

class CBubblesFIXView : public CView
{
protected: // создать только из сериализации
	CBubblesFIXView() noexcept;
	DECLARE_DYNCREATE(CBubblesFIXView)

// Атрибуты
public:
	CBubblesFIXDoc* GetDocument() const;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CBubblesFIXView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в Bubbles_FIXView.cpp
inline CBubblesFIXDoc* CBubblesFIXView::GetDocument() const
   { return reinterpret_cast<CBubblesFIXDoc*>(m_pDocument); }
#endif

