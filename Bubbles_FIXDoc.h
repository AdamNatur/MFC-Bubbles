
// Bubbles_FIXDoc.h: интерфейс класса CBubblesFIXDoc 
//

//#include "CMyTreeView.h"

#pragma once

class CMyTreeView;
class CBubblesFIXDoc;

class CMyCircle
{
public:
	CMyCircle();
	CMyCircle(int x, int y, int r, int a, int b);
	int m_iX, m_iY, m_iR, m_iA, m_iB;
	void Draw(CDC* pDC);
	void CheckImpact(int bound_x, int bound_y, CMyCircle* m_circ, int size);
	void initYourBalls(int w, int h);
};
int GetRandomNumber(int min, int max);

class CBubblesFIXDoc : public CDocument
{
protected: // создать только из сериализации
	CBubblesFIXDoc() noexcept;
	DECLARE_DYNCREATE(CBubblesFIXDoc)

// Атрибуты
public:
	CMyCircle m_circ[5];
	CMyTreeView* m_pTreeView;
	CBubblesFIXDoc* m_pDoc;
	bool m_bRed, m_bGreen, m_bBlue;
	bool m_bThin, m_bPlump, m_bBold;
	bool m_bVisible = false;
	int W = 1;
	int G;
	int R;
	int B;

	void ChangeStyle();

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CBubblesFIXDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	//virtual void OnChangedViewList();
	afx_msg void OnStyleColorBlue();
	afx_msg void OnStyleColorGreen();
	afx_msg void OnStyleColorRed();
	afx_msg void OnStyleThickness3px();
	afx_msg void OnStyleThickness6px();
	afx_msg void OnStyleThickness9px();
	afx_msg void OnStyleVisible();
	afx_msg void OnUpdateStyleVisible(CCmdUI* pCmdUI);
};
