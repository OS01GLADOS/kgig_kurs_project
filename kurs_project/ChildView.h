
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

	CRect WinRect;	// Область в окне

// Операции
public:

// Переопределение
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg void OnSize(UINT nType, int cx, int cy);
// Реализация
public:
	virtual ~CChildView();
	void set_model_parameters();
	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};

