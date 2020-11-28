
// ChildView.cpp: реализация класса CChildView
//

#include "pch.h"
#include "framework.h"
#include "kurs_project.h"
#include "ChildView.h"
#include "CMatrix.h"
#include "Top.h"

#include "CChangeParemetersDialog.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int R = 60 , r =30;

int Pview0 = 1000;
int Pview1 = 0;
int Pview2 = 50;

int Plight0 = 100;
int Plight1 = 30;
int Plight2 = 15;

int colR = 255;
int colG = 0;
int colB = 0;

bool modelParam = true;



// CChildView

CChildView::CChildView()
{
	//начальные параметры тора, освещения, наблюдателя

	PView = CMatrix();
	PLight = CMatrix();
	//step = 10;
	//m = 0;
	PView.RedimMatrix(3);

	PView(0) = Pview0; 
	PView(1) = Pview1; 
	PView(2) = Pview2;

	PLight.RedimMatrix(3);
	PLight(0) = Plight0;
	PLight(1) = Plight1;
	PLight(2) = Plight2;
	
	col = RGB(colR, colG, colB);//цвет тора
	
						 //pp = new (Top)Тор();
	pp = Top::Top(R,r);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_SET_MODEL_PARAMETERS, &CChildView::set_model_parameters)
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
	CFrameWnd* pWnd = GetParentFrame();

	CRect SpaceToDraw = WinRect;
	CPoint CurrPoint = SpaceToDraw.TopLeft();
	int startX = CurrPoint.x, startY = CurrPoint.y;
	CurrPoint = SpaceToDraw.BottomRight();
	int endX = CurrPoint.x, endY = CurrPoint.y;
	//height width
	int height = endY - startY;
	int width = endX - startX;
	int a;
	if (height > width)
		a = width;
	else
		a = height;
	CurrPoint = SpaceToDraw.CenterPoint();
	int centerX = CurrPoint.x, centerY = CurrPoint.y;


	CPaintDC dc(this); // контекст устройства для рисования

	wchar_t buffer[6];
	CString text = L"R = ";
	swprintf_s(buffer, L"%d", R);
	text.Append(buffer);
	dc.TextOutW(startX + 5, startY, text, text.GetLength());

	text = L"r = ";
	swprintf_s(buffer, L"%d", r);
	text.Append(buffer);
	dc.TextOutW(startX + 5, startX + 20, text, text.GetLength());

	text = L"Наблюдатель_R = ";
	swprintf_s(buffer, L"%d", Pview0);
	text.Append(buffer);
	dc.TextOutW(startX + 5, startY + 40, text, text.GetLength());

	text = L"Наблюдатель_Fi = ";
	swprintf_s(buffer, L"%d", Pview1);
	text.Append(buffer);
	dc.TextOutW(startX + 5, startY + 60, text, text.GetLength());

	text = L"Наблюдатель_Theta = ";
	swprintf_s(buffer, L"%d", Pview2);
	text.Append(buffer);
	dc.TextOutW(startX + 5, startY + 80, text, text.GetLength());

	text = L"Свет_R = ";
	swprintf_s(buffer, L"%d", Plight0);
	text.Append(buffer);
	dc.TextOutW(startX + 5 + 270, startY + 40, text, text.GetLength());

	text = L"Свет_Fi = ";
	swprintf_s(buffer, L"%d", Plight1);
	text.Append(buffer);
	dc.TextOutW(startX + 5 + 270, startY + 60, text, text.GetLength());

	text = L"Свет_Theta = ";
	swprintf_s(buffer, L"%d", Plight2);
	text.Append(buffer);
	dc.TextOutW(startX + 5 + 270, startY + 80, text, text.GetLength());

	text = L"Модель: ";

	if (modelParam)
		text.Append(L"Диффузная");
	else
		text.Append(L"Зеркальная");
	dc.TextOutW(startX + 5 + 100, startY + 5, text, text.GetLength());

	pp.DrawEnlighted(dc, PView, PLight, CRect(centerX - a/2, centerY - a / 2, centerX + a / 2, centerY + a / 2), col, modelParam);

}
void CChildView::set_model_parameters()
{
	CChangeParemetersDialog ParametersDialog;
	ParametersDialog.DoModal();
	if (ParametersDialog.ifRchanged())
		R = ParametersDialog.GetR();
	if(ParametersDialog.ifrchanged())
		r = ParametersDialog.Getr();

	if (ParametersDialog.ifLightRchanged())
		Plight0 = ParametersDialog.GetLightR();
	if (ParametersDialog.ifLightFichanged())
		Plight1 = ParametersDialog.GetLightFi();
	if (ParametersDialog.ifLightThetachanged())
		Plight2 = ParametersDialog.GetLightTheta();

	if (ParametersDialog.ifWatcherRchanged())
		Pview0 = ParametersDialog.GetWatcherR();
	if (ParametersDialog.ifWatcherFichanged())
		Pview1 = ParametersDialog.GetWatcherFi();
	if (ParametersDialog.ifWatcherThetachanged())
		Pview2 = ParametersDialog.GetWatcherTheta();

	if (ParametersDialog.ifColorchanged())
		col = ParametersDialog.GetChangedColor();
	if (ParametersDialog.ifModelChanged())
		modelParam = ParametersDialog.isModelDiffusial();

	PView.RedimMatrix(3);
	PView(0) = Pview0;
	PView(1) = Pview1;
	PView(2) = Pview2;

	PLight.RedimMatrix(3);
	PLight(0) = Plight0;
	PLight(1) = Plight1;
	PLight(2) = Plight2;

	pp = Top::Top(R, r);
	Invalidate();

}

void CChildView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);//для динамического изменения окна
	WinRect.SetRect(0, 0, cx , cy );//параметры окна рисования
	Invalidate();
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCount, UINT nFlags) {
	int step = 10;
	//движение наблюдателя на стрелки
	if (nChar == 37) {		//влево
		PView(1) += step;
		if (PView(1) >= 360)PView(1) -= 360;
		Invalidate();
	}
	else if (nChar == 39) {	//вправо
		PView(1) -= step;
		if (PView(1) < 0)PView(1) += 360;
		Invalidate();
	}
	else if (nChar == 38) {	//вверх
		PView(2) += step;
		if (PView(2) >= 360)PView(2) -= 360;
		Invalidate();
	}
	else if (nChar == 40) { //вниз
		PView(2) -= step;
		if (PView(2) < 0)PView(2) += 360;
		Invalidate();
	}
	//движение света на WASD
	else if (nChar == 65) {		//A
		PLight(1) -= step;
		if (PLight(1) >= 360)PLight(1) -= 360;
		Invalidate();
	}
	else if (nChar == 68) {	//D
		PLight(1) += step;
		if (PLight(1) < 0)PLight(1) += 360;
		Invalidate();
	}
	else if (nChar == 87) {	//W
		PLight(2) -= step;
		if (PLight(2) < 0)PLight(2) += 360;
		Invalidate();
	}
	else if (nChar == 83) { //S
		PLight(2) += step;
		if (PLight(2) >= 360)PLight(2) -= 360;
		Invalidate();
	}
}

