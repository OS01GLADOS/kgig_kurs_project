//���������� 3
#pragma once
#include "pch.h"
#include "GraphBitMap.h"
#include <fstream>
int counter = 0;
int ClientToBmp(HWND hWnd, char *Name)//���������� ������� ������� ���� � ����� Name.bmp, hWnd - ���������� ����, r � ������� �  ����
{	RECT r;
	GetClientRect (hWnd, &r);
	return ClientRectToBmp (hWnd, Name, r);}
int ClientRectToBmp(HWND hWnd, char* name, RECT r)	{
		HANDLE fh = CreateFile ((LPCWSTR)name, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (fh == INVALID_HANDLE_VALUE) //�� ��������
		return 2;
	BITMAPINFOHEADER bi;//��������� �������� �������� �����������
		ZeroMemory (&bi, sizeof (BITMAPINFOHEADER));//��� ��������� ������
	bi.biSize = sizeof (BITMAPINFOHEADER);
	bi.biWidth = r.right - r.left;
	bi.biHeight = r.bottom - r.top;
	bi.biPlanes = 1; 
	bi.biBitCount = 32; //16 ������� ������
	bi.biSizeImage = (bi.biWidth * bi.biBitCount + 31)/32*4*bi.biHeight;
	BITMAPFILEHEADER bmfHdr; //��������� ��� �����, ������, �������� ������� �����
		ZeroMemory (&bmfHdr, sizeof (BITMAPFILEHEADER));
	bmfHdr.bfType = 0x4D42; //BM  ('M'<<8)|'B';
	bmfHdr.bfSize = bi.biSizeImage + sizeof (BITMAPFILEHEADER) + bi.biSize;
	bmfHdr.bfReserved1 = bmfHdr.bfReserved2 = 0;
	bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)bi.biSize;
	HDC hDC = GetDC (hWnd); //�������� �����������
	HDC hDCMem = CreateCompatibleDC (hDC); //�������� ���������� ������
	HBITMAP hBitmap = CreateCompatibleBitmap (hDC, bi.biWidth, bi.biHeight);//������� ������� �����
	HBITMAP oldBitmap = (HBITMAP)SelectObject (hDCMem, hBitmap); // � �������� �������� ������ ������ ���������� ������� �����
	BitBlt (hDCMem, 0, 0, bi.biWidth, bi.biHeight, hDC, r.left, r.top, SRCCOPY); //�������� �� ������ ��������, ������� � ��� ���������
	hBitmap = (HBITMAP)SelectObject (hDCMem, oldBitmap); //�������������� ��������
	HANDLE hDIB = GlobalAlloc (GHND /*GMEM_FIXED*/, bi.biSizeImage); //���� ����� � ��� �������
	char* lp = (char*)GlobalLock (hDIB); 
	GetDIBits (hDC, hBitmap, 0, bi.biHeight, lp, (LPBITMAPINFO)&bi, DIB_RGB_COLORS);	// �� ������������
	DWORD dwWritten = sizeof (BITMAPFILEHEADER);//������ �����( ������������ ����,��������, ����� ������)
		WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);
	dwWritten = sizeof (BITMAPINFOHEADER); 
		WriteFile (fh, (LPSTR)&bi, sizeof (BITMAPINFOHEADER), &dwWritten, NULL);
	dwWritten = bi.biSizeImage;
		WriteFile (fh, lp, bi.biSizeImage, &dwWritten, NULL);
	GlobalUnlock(hDIB);    
	GlobalFree(hDIB);
	DeleteObject(hBitmap);
	lp = NULL;
	CloseHandle (fh);
	ReleaseDC (hWnd, hDCMem);
	ReleaseDC (hWnd, hDC);
	DeleteDC (hDCMem);
	DeleteDC (hDC);
	if (dwWritten == 2) return 2;
	counter++;
	return 0;}