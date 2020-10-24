// CChangeParemetersDialog.cpp: файл реализации
//

#include "pch.h"
#include "kurs_project.h"
#include "CChangeParemetersDialog.h"
#include "afxdialogex.h"


// Диалоговое окно CChangeParemetersDialog

IMPLEMENT_DYNAMIC(CChangeParemetersDialog, CDialogEx)

CChangeParemetersDialog::CChangeParemetersDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PARAMETER_CHANGE_DIALOG, pParent)
{
	
}

CChangeParemetersDialog::~CChangeParemetersDialog()
{
}

void CChangeParemetersDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CChangeParemetersDialog, CDialogEx)
	
END_MESSAGE_MAP()


// Обработчики сообщений CChangeParemetersDialog


