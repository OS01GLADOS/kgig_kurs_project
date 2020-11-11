
// kurs_project.h: основной файл заголовка для приложения kurs_project
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // основные символы


// CkursprojectApp:
// Сведения о реализации этого класса: kurs_project.cpp
//

class CkursprojectApp : public CWinApp
{
public:
	CkursprojectApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация

public:
	afx_msg void OnAppAbout();

	void make_screenshot();
	

	DECLARE_MESSAGE_MAP()
};

extern CkursprojectApp theApp;
