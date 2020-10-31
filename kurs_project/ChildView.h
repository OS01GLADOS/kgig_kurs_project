
// ChildView.h: интерфейс класса CChildView
//


#pragma once
#include "Top.h"
#include "CMatrix.h"


// Окно CChildView

class CChildView : public CWnd
{
// Создание
public:
	CChildView();

// Атрибуты
public:
	Top pp;
	CMatrix PView;
	CMatrix PLight;
	COLORREF col;
// Операции
public:

// Переопределение
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Реализация
public:
	virtual ~CChildView();

	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

