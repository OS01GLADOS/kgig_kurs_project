#pragma once

#include "CMatrix.h"
#include "LIB.H"
#include "MyGDI.h"

class Top {
public:
	int NoV;
	int NoVm;
	int NoVb;
	CRectD rs;
	CMatrix Verticles;
	//������ ���� ����������� � ������������ �����

public :
	Top(void);
	Top(int R, int r);
	void DrawEnlighted(CDC& dc, CMatrix& PView, CMatrix& PLight, CRect& RW, COLORREF col, bool);
	~Top();
};