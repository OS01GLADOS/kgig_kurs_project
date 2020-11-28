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
	afx_msg void OnBnClickedOk();
	// ввод большого R для тора

	CEdit Big_R_input;
	int R;
	bool Rchanged = false;
	afx_msg void OnEnChangeRBigInput();
	int GetR();
	bool ifRchanged();

	CEdit R_LITTLE_INPUT;
	int r;
	bool rchanged = false;
	afx_msg void OnEnChangeRLittleInput();
	int Getr();
	bool ifrchanged();


	//выше - работает

	CEdit LightR;
	int iLightR;
	bool bifLightRchanged = false;
	afx_msg void OnEnChangeLightR();
	int GetLightR();
	bool ifLightRchanged();

	CEdit LightFi;
	int iLightFi;
	bool bifLightFichanged = false;
	afx_msg void OnEnChangeLightFi();
	int GetLightFi();
	bool ifLightFichanged();

	CEdit LightTheta;
	int iLightTheta;
	bool bifLightThetachanged = false;
	afx_msg void OnEnChangeLightTheta();
	int GetLightTheta();
	bool ifLightThetachanged();




	CEdit WatcherR;
	int iWatcherR;
	bool bifWatcherRchanged = false;
	afx_msg void OnEnChangeWatcherR();
	int GetWatcherR();
	bool ifWatcherRchanged();

	CEdit WatcherFi;
	int iWatcherFi;
	bool bifWatcherFichanged = false;
	afx_msg void OnEnChangeWatcherFi();
	int GetWatcherFi();
	bool ifWatcherFichanged();


	CEdit WatcherTheta;
	int iWatcherTheta;
	bool bifWatcherThetachanged = false;
	afx_msg void OnEnChangeWatcherTheta();
	int GetWatcherTheta();
	bool ifWatcherThetachanged();
	

	bool diffusModel = true;
	bool bisModelChanged = false;
	CButton RadioDiffuselModel;
	afx_msg void OnBnClickedDiffuseModel();
	CButton MirrorModel;
	afx_msg void OnBnClickedMirrorModel();
	bool isModelDiffusial();
	bool ifModelChanged();


	COLORREF ChangedColor;
	bool bifColorchanged = false;
	CMFCColorButton ColorSelect;
	afx_msg void OnBnClickedMfccolorbutton1();
	COLORREF GetChangedColor();
	bool ifColorchanged();
};
