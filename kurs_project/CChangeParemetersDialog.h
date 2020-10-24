#pragma once


// Диалоговое окно CChangeParemetersDialog

class CChangeParemetersDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeParemetersDialog)

public:
	CChangeParemetersDialog(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CChangeParemetersDialog();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PARAMETER_CHANGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()

public:
};
