
// Bubbles_FIX.h: основной файл заголовка для приложения Bubbles_FIX
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CBubblesFIXApp:
// Сведения о реализации этого класса: Bubbles_FIX.cpp
//

class CBubblesFIXApp : public CWinApp
{
public:
	CBubblesFIXApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBubblesFIXApp theApp;
