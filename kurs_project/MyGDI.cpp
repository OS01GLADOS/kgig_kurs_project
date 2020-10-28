#pragma once
#include "pch.h"
#include "MyGDI.h"
#include "CMatrix.h"

const double pi = 3.14159265358979;

//получение оконных координат по видовым
//CMatrix SpaceToWindow(CRectD& rs, CRect& rw) 
CMatrix SpaceToWindow(CRect& rs, CRect& rw)
{
	CMatrix m(3, 3);
	double kx = (rw.right - rw.left) / (rs.right - rs.left);
	double ky = (rw.bottom - rw.top) / (rs.top - rs.bottom);
	m(2, 2) = 1;
	m(0, 0) = kx;
	m(1, 1) = -ky;
	m(0, 2) = rw.left - kx * rs.left;
	m(1, 2) = rw.top - ky * rs.bottom;
	return m;
}
//векторное произведение векторов
CMatrix VectorMult(CMatrix V1, CMatrix V2) {
	CMatrix m(3), a(3, 3);
	a(0, 1) = -V1(2);
	a(0, 2) = V1(1);
	a(1, 2) = -V1(0);
	a(1, 0) = V1(2);
	a(2, 0) = -V1(1);
	a(2, 1) = V1(0);
	m = a * V2;
	return m;
}
//скалярное произведение векторов
double ScalarMult(CMatrix V1, CMatrix V2) {
	return V1(0)*V2(0) + V1(1)*V2(1) + V1(2)*V2(2);
}

//косинус угла между векторами
double cosViV2(CMatrix V1, CMatrix V2) {
	return ScalarMult(V1, V2) / (V1.Abs()*V2.Abs());
}
//получение декартовых координат по сферическим
CMatrix SphereToCart(CMatrix DView) {
	CMatrix Ve(3);
	double fi_r = (DView(1))*pi / 180;
	double theta_r = DView(2)*pi / 180;
	Ve(0) = DView(0)*sin(theta_r)*cos(fi_r);
	Ve(1) = DView(0)*sin(theta_r)*sin(fi_r);
	Ve(2) = DView(0)*cos(theta_r);
	return Ve;
}


//получение видовых координат по положению наблюдателя CMatrix CreateViewCoord
CMatrix CreateViewCoord(double R, double fi, double theta) {
	CMatrix Ve(4, 4), Mz(4, 4);
	Mz(0, 0) = -1; Mz(1, 1) = 1; Mz(2, 2) = 1; Mz(3, 3) = 1;
	double fi_r = fi * pi / 180;
	double theta_r = theta * pi / 180;
	Ve = Mz * Rotate3Dx(180 - theta)*Rotate3Dz(90 - fi);
	return Ve;
}
