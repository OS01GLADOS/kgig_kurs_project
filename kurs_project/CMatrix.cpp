#include "pch.h"
#include "CMatrix.h"
#include <windows.h>
#include <cmath>

const double pi = 3.14159265358979;

CMatrix::CMatrix()
{
 n_rows=1;
 n_cols=1;
 array=new double*[n_rows];
 for(int i=0;i<n_rows;i++) array[i]=new double[n_cols];
 for(int i=0;i<n_rows;i++)
   for(int j=0;j<n_cols;j++) array[i][j]=0;
 }

//-------------------------------------------------------------------------------
CMatrix::CMatrix(int Nrow,int Ncol)
// Nrow - ����� �����
// Ncol - ����� ��������
{
 n_rows=Nrow;
 n_cols=Ncol;
 array=new double*[n_rows];
 for(int i=0;i<n_rows;i++) array[i]=new double[n_cols];
 for(int i=0;i<n_rows;i++)
   for(int j=0;j<n_cols;j++) array[i][j]=0;
 }

//---------------------------------------------------------------------------------
CMatrix::CMatrix(int Nrow)  //������
// Nrow - ����� �����
{
 n_rows=Nrow;
 n_cols=1;
 array=new double*[n_rows];
 for(int i=0;i<n_rows;i++) array[i]=new double[n_cols];
 for(int i=0;i<n_rows;i++)
   for(int j=0;j<n_cols;j++) array[i][j]=0;
 }
//---------------------------------------------------------------------------------
CMatrix::~CMatrix()
{
 for(int i=0;i<n_rows;i++) delete array[i];
 delete array;
}

//---------------------------------------------------------------------------------
double &CMatrix::operator()(int i,int j)
// i - ����� ������
// j - ����� �������
{
if ((i>n_rows-1)||(j>n_cols-1))     //  �������� ������ �� ��������
   {
		 TCHAR* error=TEXT("CMatrix::operator(int,int): ����� ������� �� ������� ��������� ");
		 MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
     exit(1);
   }
return array[i][j];
}

//---------------------------------------------------------------------------------
double &CMatrix::operator()(int i)
// i - ����� ������ ��� �������
{
if (n_cols>1)     //  ����� �������� ������ ������
   {
	   TCHAR* error = TEXT("CMatrix::operator(int): ������ �� ������ - ����� �������� ������ 1 ");
	   MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
    exit(1);
   }
if (i>n_rows-1)     //  �������� ������ �� ��������
   {
		TCHAR* error=TEXT("CMatrix::operator(int): ����� ������� �� ������� ��������� ");
		MessageBox(NULL,error,TEXT("������"),MB_ICONSTOP);
    exit(1);
   }
return array[i][0];
}
//---------------------------------------------------------------------------------
CMatrix CMatrix::operator-()
// �������� -M
{
	CMatrix Temp(n_rows,n_cols);
  for(int i=0;i<n_rows;i++)
	for(int j=0;j<n_cols;j++) Temp(i,j)=-array[i][j];
  return Temp;
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::operator+(CMatrix& M)
// �������� M1+M2
{	
	int bb=(n_rows==M.rows())&&(n_cols==M.cols());
	if(!bb)
	{ 
		TCHAR* error = TEXT("CMatrix::operator(+): �������������� ������������ ������ ");
		MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
    exit(1);
	}
	CMatrix Temp(*this);
  for(int i=0;i<n_rows;i++)
	for(int j=0;j<n_cols;j++) Temp(i,j)+=M(i,j);
  return Temp;
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::operator-(CMatrix& M)
// �������� M1-M2
{	
	int bb=(n_rows==M.rows())&&(n_cols==M.cols());
	if(!bb)
	{ 
		TCHAR* error = TEXT("CMatrix::operator(-): �������������� ������������ ������ ");
		MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
    exit(1);
	}
	CMatrix Temp(*this);
	for(int i=0;i<n_rows;i++)
	for(int j=0;j<n_cols;j++) Temp(i,j)-=M(i,j);
  return Temp;
}
//---------------------------------------------------------------------------------
CMatrix CMatrix::operator*(CMatrix& M)
// ��������� �� ������� M
{
double sum;
int nn=M.rows();
int mm=M.cols();
CMatrix Temp(n_rows,mm);
if (n_cols==nn)
  {
   for (int i=0;i<n_rows;i++)
        for (int j=0;j<mm;j++)
          {
          sum=0;
          for (int k=0;k<n_cols;k++) sum+=(*this)(i,k)*M(k,j);
          Temp(i,j)=sum;
          }
  }
else
 {
   TCHAR* error=TEXT("CMatrix::operator*: �������������� ������������ ������ ");
   MessageBox(NULL,error,TEXT("������"),MB_ICONSTOP);
   exit(1);
  }
return Temp;
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::operator=(const CMatrix& M)
// �������� ������������ M1=M
{
if (this==&M) return *this;
int nn=M.rows();
int mm=M.cols();
if ((n_rows==nn)&&(n_cols==mm))
 {
for (int i=0;i<n_rows;i++)
     for (int j=0;j<n_cols;j++) array[i][j]=M.array[i][j];
 }
else   // ��� ������ ������������
  {
   TCHAR* error=TEXT("CMatrix::operator=: �������������� ������������ ������");
   MessageBox(NULL,error,TEXT("������"),MB_ICONSTOP);
   exit(1);
  }
return *this;
}

//---------------------------------------------------------------------------------
CMatrix::CMatrix(const CMatrix &M) // ����������� �����������
{
	n_rows=M.n_rows;
	n_cols=M.n_cols;
	array=new double*[n_rows];
	for(int i=0;i<n_rows;i++) array[i]=new double[n_cols];
	for(int i=0;i<n_rows;i++)
    for(int j=0;j<n_cols;j++) array[i][j]=M.array[i][j];
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::operator+(double x)
// �������� M+x, ��� M - �������, x - �����
{
  CMatrix Temp(*this);
  for(int i=0;i<n_rows;i++)
	for(int j=0;j<n_cols;j++) Temp(i,j)+=x;
  return Temp;
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::operator-(double x)
// �������� M+x, ��� M - �������, x - �����
{
  CMatrix Temp(*this);
  for(int i=0;i<n_rows;i++)
	for(int j=0;j<n_cols;j++) Temp(i,j)-=x;
  return Temp;
}



//---------------------------------------------------------------------------------
CMatrix CMatrix::Transp()
// ���������� �������,����������������� � (*this)
{
  CMatrix Temp(n_cols,n_rows);
  for (int i=0;i<n_cols;i++)
     for (int j=0;j<n_rows;j++) Temp(i,j)=array[j][i];
  return Temp;
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::GetRow(int k)	
// ���������� ������ ������� �� ������ k
{
	if(k>n_rows-1)
	{
		TCHAR* error = TEXT("CMatrix::GetRow(int k): �������� k ��������� ����� ����� ");
		MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
    exit(1);
	}
	CMatrix M(1,n_cols);
	for(int i=0;i<n_cols;i++)M(0,i)=(*this)(k,i);
	return M;
}
//---------------------------------------------------------------------------------
CMatrix CMatrix::GetRow(int k,int n,int m)	
// ���������� ��������� �� ������ ������� � ������� k
// n - ����� ������� �������� � ������
// m - ����� ���������� �������� � ������
{
	int b1=(k>=0)&&(k<n_rows);
	int b2=(n>=0)&&(n<=m);
	int b3=(m>=0)&&(m<n_cols);
	int b4=b1&&b2&&b3;
	if(!b4)
	{
		TCHAR* error = TEXT("CMatrix::GetRow(int k,int n, int m):������ � ���������� ");
		MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
    exit(1);
	}
	int nCols=m-n+1;
	CMatrix M(1,nCols);
	for(int i=n;i<=m;i++)M(0,i-n)=(*this)(k,i);
	return M;
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::GetCol(int k)	
// ���������� ������� ������� �� ������ k
{
	if(k>n_cols-1)
	{
		TCHAR* error = TEXT("CMatrix::GetCol(int k): �������� k ��������� ����� �������� ");
		MessageBox(NULL, error, TEXT("������"), MB_ICONSTOP);
    exit(1);
	}
	CMatrix M(n_rows,1);
	for(int i=0;i<n_rows;i++)M(i,0)=(*this)(i,k);
	return M;
}
//---------------------------------------------------------------------------------
CMatrix CMatrix::GetCol(int k,int n, int m)
// ���������� ���������� �� ������� ������� � ������� k
// n - ����� ������� �������� � �������
// m - ����� ���������� �������� � �������
{
	int b1=(k>=0)&&(k<n_cols);
	int b2=(n>=0)&&(n<=m);
	int b3=(m>=0)&&(m<n_rows);
	int b4=b1&&b2&&b3;
	if(!b4)
	{
		TCHAR* error = TEXT("CMatrix::GetCol(int k,int n, int m):������ � ���������� ");
		MessageBox(NULL,error,TEXT("������"),MB_ICONSTOP);
    exit(1);
	}
	int nRows=m-n+1;
	CMatrix M(nRows,1);
	for(int i=n;i<=m;i++)M(i-n,0)=(*this)(i,k);
	return M;
}
//---------------------------------------------------------------------------------
CMatrix CMatrix::RedimMatrix(int NewRow,int NewCol)
// �������� ������ ������� � ������������ ������
// NewRow - ����� ����� �����
// NewCol - ����� ����� �������� 
{
	for(int i=0;i<n_rows;i++) delete array[i];
	delete array;
	n_rows=NewRow;
	n_cols=NewCol;
	array=new double*[n_rows];
	for(int i=0;i<n_rows;i++) array[i]=new double[n_cols];
	for(int i=0;i<n_rows;i++)
		for(int j=0;j<n_cols;j++) array[i][j]=0;
	return (*this);
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::RedimData(int NewRow,int NewCol)
// �������� ������ ������� � ����������� ������, ������� ����� ���������
// NewRow - ����� ����� �����
// NewCol - ����� ����� �������� 
{
	CMatrix Temp=(*this);
	this->RedimMatrix(NewRow,NewCol);
	int min_rows=Temp.rows()<(*this).rows()?Temp.rows():(*this).rows();
	int min_cols=Temp.cols()<(*this).cols()?Temp.cols():(*this).cols();
	for(int i=0;i<min_rows;i++)
		for(int j=0;j<min_cols;j++) (*this)(i,j)=Temp(i,j);
	return (*this);
}


//---------------------------------------------------------------------------------
CMatrix CMatrix::RedimMatrix(int NewRow)
// �������� ������ ������� � ������������ ������
// NewRow - ����� ����� �����
// NewCol=1
{
	for(int i=0;i<n_rows;i++) delete array[i];
	delete array;
	n_rows=NewRow;
	n_cols=1;
	array=new double*[n_rows];
	for(int i=0;i<n_rows;i++) array[i]=new double[n_cols];
	for(int i=0;i<n_rows;i++)
		for(int j=0;j<n_cols;j++) array[i][j]=0;
	return (*this);
}

//---------------------------------------------------------------------------------
CMatrix CMatrix::RedimData(int NewRow)
// �������� ������ ������� � ����������� ������, ������� ����� ���������
// NewRow - ����� ����� �����
// NewCol=1
{
	CMatrix Temp=(*this);
	this->RedimMatrix(NewRow);
	int min_rows=Temp.rows()<(*this).rows()?Temp.rows():(*this).rows();	
	for(int i=0;i<min_rows;i++)(*this)(i)=Temp(i);	
	return (*this);
}
//----------------------------------------------------------------------------------
double CMatrix::MaxElement()
// ������������ �������� ��������� �������
{
	double max=(*this)(0,0);
	for(int i=0;i<(this->rows());i++)
	  for(int j=0;j<(this->cols());j++) if ((*this)(i,j)>max) max=(*this)(i,j);
	return max;
}

//----------------------------------------------------------------------------------
double CMatrix::MinElement()
// ����������� �������� ��������� �������
{
	double min=(*this)(0,0);
	for(int i=0;i<(this->rows());i++)
	  for(int j=0;j<(this->cols());j++) if ((*this)(i,j)<min) min=(*this)(i,j);
	return min;
}

double CMatrix::Abs() {
	double powSum=0;
	for (int i = 0; i < n_cols; i++) {
		powSum += pow(array[i][0],2);
	}
	return sqrt(powSum);
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

CMatrix Translate2D(double x, double y) { //�������� � ���������� ������� ���������
	CMatrix m(3, 3);
	m(0, 0) = 1; m(1, 1) = 1; m(2, 2) = 1;
	m(0, 2) = x;
	m(1, 2) = y;
	return m;
}
CMatrix Rotate2D(double fi) { //������� � ���������� ������� ���������
	CMatrix m(3, 3);
	double fi_r = fi * pi / 180.0;
	m(0, 0) = cos(fi_r);
	m(1, 1) = cos(fi_r);
	m(2, 2) = 1;
	m(0, 1) = -sin(fi_r);
	m(1, 0) = sin(fi_r);
	return m;
}
//�������� � ���������� ������� ���������
CMatrix Translate3D(double x, double y, double z) {
	CMatrix m(4, 4);
	m(0, 0) = 1; m(1, 1) = 1; m(2, 2) = 1; m(3, 3) = 1;
	m(0, 3) = x;
	m(1, 3) = y;
	m(2, 3) = z;
	return m;
}
//������� ������ ��� �Z
CMatrix Rotate3Dz(double fi) {
	CMatrix m(4, 4);
	double fi_r = fi * pi / 180.0;
	m(0, 0) = cos(fi_r);
	m(1, 1) = cos(fi_r);
	m(2, 2) = 1; m(3, 3) = 1;
	m(0, 1) = -sin(fi_r);
	m(1, 0) = sin(fi_r);
	return m;
}
//������� ������ ��� ��
CMatrix Rotate3Dx(double fi) {
	CMatrix m(4, 4);
	double fi_r = fi * pi / 180.0;
	m(1, 1) = cos(fi_r);
	m(2, 2) = cos(fi_r);
	m(0, 0) = 1; m(3, 3) = 1;
	m(1, 2) = -sin(fi_r);
	m(2, 1) = sin(fi_r);
	return m;
}
//������� ������ ��� �Y
CMatrix Rotate3Dy(double fi) {
	CMatrix m(4, 4);
	double fi_r = fi * pi / 180.0;
	m(0, 0) = cos(fi_r);
	m(2, 2) = cos(fi_r);
	m(1, 1) = 1; m(3, 3) = 1;
	m(0, 2) = -sin(fi_r);
	m(2, 0) = sin(fi_r);
	return m;
}

