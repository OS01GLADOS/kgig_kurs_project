#pragma once

#include "CMatrix.h"

class Top {
public:
	CRect rs;
	CMatrix Verticles;
	//������ ���� ����������� � ������������ �����
	int NoV;
	int NoVm;
	int NoVb;
public :
	Top(void);
	Top(int R, int r);
	void DrawEnlighted(CDC& dc, CMatrix& PView, CMatrix& PLight, CRect& RW, COLORREF col, bool);
	~Top();
};