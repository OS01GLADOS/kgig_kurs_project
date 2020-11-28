#include "pch.h"
#include "Top.h"
#include "CMatrix.h"
#include "MyGDI.h"

#define NOV 100

#define NOVB 20
#define NOVM 100

const double pi = 3.14159265358979;

void Top::DrawEnlighted(CDC& dc, CMatrix& PView, CMatrix& PLight, CRect& RW, COLORREF col, bool isDiffusel) {
	try {
		CPen* pn = new CPen(PS_NULL, 0, RGB(0, 0, 0)/*RGB(0, 0, 0)*/);
		dc.SelectObject(pn);
		double R = GetRValue(col), G = GetGValue(col), B = GetBValue(col);
		double Kd = 1, Ks = 1, I = 1, Lights = 0;//Lights = 0
		//преобразование сферических координат наблюдателя в декартовы
		CMatrix ViewCart = SphereToCart(PView);
		//преобразование сферических координат источника света в декартовы
		CMatrix LightCart = SphereToCart(PLight);
		//матрица пересчета из мировых координат в видовые (МСК->ВСК)
		CMatrix MV = CreateViewCoord(PView(0), PView(1), PView(2));
		//матрица пересчета из видовых в оконные(ВСК->ОСК)
		CMatrix K = SpaceToWindow(rs, RW);
		//точки в ВСК
		CMatrix ViewVert(4, NoV);
		//точки в ОСК
		CPoint MasVert[NOV*NOV];
		for (int i = 0; i < NoV; i++) {
			CMatrix V = MV * Verticles.GetCol(i);	//пересчет МСК->ВСК
			V(2) = 1;
			CMatrix W = K * V.GetCol(0, 0, 2);		//пересчет ВСК->ОСК
			double v0 = V(0), v1 = V(1), v2 = V(2);
			double w0 = W(0), w1 = W(1), w2 = W(2);
			for (int j = 0; j < 3; j++) {
				ViewVert(j, i) = W(j);
			}
			MasVert[i].x = W(0);
			MasVert[i].y = W(1);
		}
		CMatrix VE(3), R1(3), R2(3), V1(3), V2(3), VN(3);
		double sm;

		int j1 = (PView(1) / 180 * NoVb / 2);
		if (j1 >= NoVb)j1 = 0;
		int j0 = j1 + NoVb / 2;
		if (j0 > NoVb)j0 -= NoVb;
		if (PView(2) > 180) {
			j0 += NoVb / 2;
			if (j0 >= NoVb)j0 -= NoVb;
			j1 += NoVb / 2;
			if (j1 >= NoVb)j1 -= NoVb;
		}

		for (int jr = j0, jl = j0;; jr++, jl--) {//обход большого круга
			if (jr >= NoVb)
				jr = 0;
			int lr = jr + 1;//номер следующего малого круга
			if (lr >= NoVb)
				lr = 0;
			int i0 = (PView(2) / 180 * NoVm / 2), i1 = i0 - 1;
			if (i1 < 0)i1 = NoVm - 1;

			


			for (int i = i0;; i--) {//обход малых кругов
				if (i < 0)
					i = NoVm - 1;
				int k = i - 1;//номер следующей точки малого круга
				if (k < 0)
					k = NoVm-1;
				R1 = Verticles.GetCol(k + jr * NoVm, 0, 2);//текущая точка на малом круге
				R2 = Verticles.GetCol(i + jr * NoVm, 0, 2);//следующая точка на малом круге
				VE = Verticles.GetCol(i + lr * NoVm, 0, 2);//точка на следующем малом круге
				V1 = R2 - R1; V2 = VE - R1;
				VN = VectorMult(V2, V1);//вектор нормали

				sm = ScalarMult(VN, ViewCart);
				//проверка видимости грани   (sm >= 0)
				if (ScalarMult(VN, LightCart) >= 0 && (sm >= 0)) {
					//расчет освещенности для диффузионной модели освещения
					if (isDiffusel)
						Lights = ((int)(cosViV2(VN, LightCart) * 100)) / 100;
					//Lights = (int)(I*Kd*cosViV2(VN, LightCart));
					else {
						Lights = ((int)   cosViV2(VN, ViewCart)  * 100)   / 100;
					}
					//расчёт освещённости для диффузной модели освещения
					if (Lights !=0)
						Lights = 1 - Lights;
				}
				else Lights = 0;

		

				//Lights = 0.5;

				//прорисовка полигона
				CPoint* p = new CPoint[4];
				p[0] = MasVert[i + jr * NoVm];
				p[1] = MasVert[k + jr * NoVm];
				p[2] = MasVert[k + lr * NoVm];
				p[3] = MasVert[i + lr * NoVm];
				CBrush* br = new CBrush(RGB(R*Lights, G*Lights, B*Lights));
				dc.SelectObject(br);
				dc.Polygon(p, 4);
				delete br;

				if (k == i0)
					break;
			}


			//
			if (jl >= NoVb)jl = 0;
			if (jl < 0)
				jl = NoVb - 1;
			int ll = jl + 1;//номер следующего малого круга
			if (ll >= NoVb)
				ll = 0;
			i0 = (PView(2) / 180 * NoVm / 2);
			i1 = i0 - 1;
			if (i1 < 0)i1 = NoVm - 1;


				for (int i = i0;; i--) {//обход малых кругов
					if (i < 0)
						i = NoVm - 1;
					int k = i - 1;//номер следующей точки малого круга
					if (k < 0)
						k = NoVm - 1;
					R1 = Verticles.GetCol(k + jr * NoVm, 0, 2);//текущая точка на малом круге
					R2 = Verticles.GetCol(i + jr * NoVm, 0, 2);//следующая точка на малом круге
					VE = Verticles.GetCol(i + lr * NoVm, 0, 2);//точка на следующем малом круге
				V1 = R2 - R1; V2 = VE - R1;
				VN = VectorMult(V2, V1);//вектор нормали

				sm = ScalarMult(VN, ViewCart);
				if (true) {//проверка видимости грани (sm >= 0)
					if (ScalarMult(VN, LightCart) >= 0 && sm >= 0) {
						//расчет освещенности для диффузионной модели освещения
						if (isDiffusel)
							Lights = ( (int)(  cosViV2(VN, LightCart) *100  ) )/100;

						else {
							Lights = ((int) ( cosViV2(VN, ViewCart)  *100 ) ) /100;
						}
						//расчет освещенности для зеркальной модели освещения
						if (Lights != 0)
							Lights = 1 - Lights;
					}
					else Lights = 0;

					//прорисовка полигона
					CPoint* p = new CPoint[4];
					p[0] = MasVert[k + jl * NoVm];
					p[1] = MasVert[i + jl * NoVm];
					p[2] = MasVert[i + ll * NoVm];
					p[3] = MasVert[k + ll * NoVm];
					CBrush* br = new CBrush(RGB(R*Lights, G*Lights, B*Lights));
					dc.SelectObject(br);
					dc.Polygon(p, 4);
					delete br;
				}
				if (k == i0)break;
			}
			if (jr == j1)break;
		}
		delete pn;
	}
	catch (...) {

	}
}

Top::Top(void)
{

	NoV = NOVM*NOVM;
	NoVm = NOVM;
	NoVb = NOVM;

	Verticles = CMatrix();
	Verticles.RedimMatrix(4, NoV);
	int R = 60, r = 20, i = 0;
	//установка координат точек тора в зависимости от радиусов
	for (double beta = -pi; beta <= pi - pi / NoVb; beta += pi / NoVb * 2) {//обход большого круга
		for (double alpha = 0; alpha < pi * 2 - pi / NoVm; alpha += pi / NoVm * 2) {//обход малых кругов
			Verticles(0, i) = (R + r * cos(alpha))*cos(beta);
			Verticles(1, i) = (R + r * cos(alpha))*sin(beta);
			Verticles(2, i) = r * sin(alpha);
			Verticles(3, i) = 1;
			i++;
		}
	}
	//rs = CRectD(-100, -100, 100, 100);
	rs = CRect(-100, -100, 100, 100);
}

Top::Top(int R, int r)
{
	NoV = NOV * NOV;
	NoVm = NOVM;
	NoVb = NOVB;

	Verticles.RedimMatrix(4, NoV);
	int i = 0;
	//установка координат точек тора в зависимости от заданных радиусов
	for (double beta = -pi; beta <= pi - pi / NoVb; beta += pi / NoVb * 2) {//обход большого круга
		for (double alpha = 0; alpha < pi * 2 - pi / NoVm; alpha += pi / NoVm * 2) {//обход малых кругов
			Verticles(0, i) = (R + r * cos(alpha))*cos(beta);
			Verticles(1, i) = (R + r * cos(alpha))*sin(beta);
			Verticles(2, i) = r * sin(alpha);
			Verticles(3, i) = 1;
			i++;
		}
	}
	//rs = CRectD(-100, -100, 100, 100);
	rs = CRect(-100, -100, 100, 100);

}

Top::~Top(void)
{
}
