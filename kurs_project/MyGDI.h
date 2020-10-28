#pragma once
#include "CMatrix.h"

//CMatrix SpaceToWindow(CRectD& rs, CRect& rw);
CMatrix SpaceToWindow(CRect& rs, CRect& rw);
CMatrix VectorMult(CMatrix V1, CMatrix V2);
double ScalarMult(CMatrix V1, CMatrix V2);
double cosViV2(CMatrix V1, CMatrix V2);
CMatrix SphereToCart(CMatrix DView);
CMatrix CreateViewCoord(double R, double fi, double theta);