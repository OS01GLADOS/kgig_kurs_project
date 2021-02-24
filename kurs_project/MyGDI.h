#pragma once
#include "pch.h"
#include "math.h"
#include "cmatrix.h"
#include "lib.h"


CMatrix SpaceToWindow(CRectD& rs, CRect& rw);
CMatrix VectorMult(CMatrix V1, CMatrix V2);
double ScalarMult(CMatrix V1, CMatrix V2);
double cosViV2(CMatrix V1, CMatrix V2);
CMatrix SphereToCart(CMatrix DView);
CMatrix CreateViewCoord(double theta, double fi, double R);

CMatrix Translate3D(double x, double y, double z);
CMatrix Rotate3Dx(double fi);
CMatrix Rotate3Dy(double fi);
CMatrix Rotate3Dz(double fi);