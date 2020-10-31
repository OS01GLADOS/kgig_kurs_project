
// ChildView.cpp: реализация класса CChildView
//

#include "pch.h"
#include "framework.h"
#include "kurs_project.h"
#include "ChildView.h"
#include "CMatrix.h"
#include "Top.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	//начальные параметры тора, освещения, наблюдателя

	PView = CMatrix();
	PLight = CMatrix();
	//step = 10;
	//m = 0;
	PView.RedimMatrix(3);
	PView(0) = 450; PView(1) = 0; PView(2) = 45;
	PLight.RedimMatrix(3);
	PLight(0) = 450; PLight(1) = 90; PLight(2) = 45;
	col = RGB(255, 200, 150);
	//pp = new (Top)Тор();
	pp = Top::Top();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// Обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // контекст устройства для рисования

	/*
	dc.MoveTo(100, 100);
	dc.LineTo(0, 100);
	dc.LineTo(167, 200);
	dc.LineTo(322, 3);
*/

	pp.DrawEnlighted(dc, PView, PLight, CRect(0, 0, 550, 550), col);

	// TODO: Добавьте код обработки сообщений
	
	// Не вызывайте CWnd::OnPaint() для сообщений рисования
}

