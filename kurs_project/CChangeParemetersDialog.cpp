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
	//DDX_Control(pDX, IDC_R_BIG_INPUT,);

	DDX_Control(pDX, IDC_R_BIG_INPUT, Big_R_input);
	DDX_Control(pDX, IDC_R_LITTLE_INPUT, R_LITTLE_INPUT);
	DDX_Control(pDX, IDC_LIGHT_R, LightR);
	DDX_Control(pDX, IDC_LIGHT_FI, LightFi);
	DDX_Control(pDX, IDC_LIGHT_THETA, LightTheta);
	DDX_Control(pDX, IDC_WATCHER_R, WatcherR);
	DDX_Control(pDX, IDC_WATCHER_FI, WatcherFi);
	DDX_Control(pDX, IDC_WATCHER_THETA, WatcherTheta);
	DDX_Control(pDX, IDC_DIFFUSE_MODEL, RadioDiffuselModel);
	DDX_Control(pDX, IDD_MIRROR_MODEL, MirrorModel);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, ColorSelect);
}


BEGIN_MESSAGE_MAP(CChangeParemetersDialog, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &CChangeParemetersDialog::OnBnClickedOk)

	ON_EN_CHANGE(IDC_R_BIG_INPUT, &CChangeParemetersDialog::OnEnChangeRBigInput)
	ON_EN_CHANGE(IDC_R_LITTLE_INPUT, &CChangeParemetersDialog::OnEnChangeRLittleInput)

	ON_EN_CHANGE(IDC_LIGHT_R, &CChangeParemetersDialog::OnEnChangeLightR)
	ON_EN_CHANGE(IDC_LIGHT_FI, &CChangeParemetersDialog::OnEnChangeLightFi)
	ON_EN_CHANGE(IDC_LIGHT_THETA, &CChangeParemetersDialog::OnEnChangeLightTheta)

	ON_EN_CHANGE(IDC_WATCHER_R, &CChangeParemetersDialog::OnEnChangeWatcherR)
	ON_EN_CHANGE(IDC_WATCHER_FI, &CChangeParemetersDialog::OnEnChangeWatcherFi)
	ON_EN_CHANGE(IDC_WATCHER_THETA, &CChangeParemetersDialog::OnEnChangeWatcherTheta)
	ON_BN_CLICKED(IDC_DIFFUSE_MODEL, &CChangeParemetersDialog::OnBnClickedDiffuseModel)
	ON_BN_CLICKED(IDD_MIRROR_MODEL, &CChangeParemetersDialog::OnBnClickedMirrorModel)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CChangeParemetersDialog::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// Обработчики сообщений CChangeParemetersDialog


int returnNormalAngle(int angleIn) {
	int angle = angleIn;
	if (angle >= 360)
	{
		angle -= 360;
		angle = returnNormalAngle(angle);
	}
	return angle;
	
}

void CChangeParemetersDialog::OnBnClickedOk()
{
	CDialogEx::OnOK();
}

void CChangeParemetersDialog::OnEnChangeRBigInput()
{
	CString* s = new CString();
	Big_R_input.GetWindowText(*s);
	CString input = *s;
	try {
		R = _ttoi(input);
		Rchanged = true;
	}
	catch (...) {

	}
}
int CChangeParemetersDialog::GetR() {
	return R;
}
bool CChangeParemetersDialog::ifRchanged() {
	return Rchanged;
}

void CChangeParemetersDialog::OnEnChangeRLittleInput()
{
	CString* s = new CString();
	R_LITTLE_INPUT.GetWindowText(*s);
	CString input = *s;
	try {
		r = _ttoi(input);
		rchanged = true;
	}
	catch (...)
	{

	}
}
int CChangeParemetersDialog::Getr() {
	return r;
}
bool CChangeParemetersDialog::ifrchanged() {
	return rchanged;
}
//выше всё работает хорошо


void CChangeParemetersDialog::OnEnChangeLightR()
{
	CString* s = new CString();
	LightR.GetWindowText(*s);
	CString input = *s;

		iLightR = _ttoi(input);
		bifLightRchanged = true;

}
int CChangeParemetersDialog::GetLightR() {
	return iLightR;
}
bool CChangeParemetersDialog::ifLightRchanged() {
	return bifLightRchanged;
}

void CChangeParemetersDialog::OnEnChangeLightFi()
{
	CString* s = new CString();
	LightFi.GetWindowText(*s);
	CString input = *s;
	try {
		iLightFi = _ttoi(input);
		iLightFi = returnNormalAngle(iLightFi);
		bifLightFichanged = true;
	}
	catch (...)
	{

	}
}
int CChangeParemetersDialog::GetLightFi() {
	return iLightFi;
}
bool CChangeParemetersDialog::ifLightFichanged() {
	return bifLightFichanged;
}

void CChangeParemetersDialog::OnEnChangeLightTheta()
{
	CString* s = new CString();
	LightTheta.GetWindowText(*s);
	CString input = *s;
	try {
		iLightTheta = _ttoi(input);
		iLightTheta = returnNormalAngle(iLightTheta);
		bifLightThetachanged = true;
	}
	catch (...)
	{

	}
}
int CChangeParemetersDialog::GetLightTheta() {
	return iLightTheta;
}
bool CChangeParemetersDialog::ifLightThetachanged() {
	return bifLightThetachanged;
}



void CChangeParemetersDialog::OnEnChangeWatcherR()
{
	CString* s = new CString();
	WatcherR.GetWindowText(*s);
	CString input = *s;

	iWatcherR = _ttoi(input);
	bifWatcherRchanged = true;
}
int CChangeParemetersDialog::GetWatcherR() {
	return iWatcherR;
}
bool CChangeParemetersDialog::ifWatcherRchanged() {
	return bifWatcherRchanged;
}

void CChangeParemetersDialog::OnEnChangeWatcherFi()
{
	CString* s = new CString();
	WatcherFi.GetWindowText(*s);
	CString input = *s;
	try {
		iWatcherFi = _ttoi(input);
		iWatcherFi = returnNormalAngle(iWatcherFi);
		bifWatcherFichanged = true;
	}
	catch (...)
	{

	}
}
int CChangeParemetersDialog::GetWatcherFi() {
	return iWatcherFi;
}
bool CChangeParemetersDialog::ifWatcherFichanged() {
	return bifWatcherFichanged;
}

void CChangeParemetersDialog::OnEnChangeWatcherTheta()
{
	CString* s = new CString();
	WatcherTheta.GetWindowText(*s);
	CString input = *s;
	try {
		iWatcherTheta = _ttoi(input);
		iWatcherTheta = returnNormalAngle(iWatcherTheta);
		bifWatcherThetachanged = true;
	}
	catch (...)
	{

	}
}
int CChangeParemetersDialog::GetWatcherTheta() {
	return iWatcherTheta;
}
bool CChangeParemetersDialog::ifWatcherThetachanged() {
	return bifWatcherThetachanged;
}




void CChangeParemetersDialog::OnBnClickedDiffuseModel()
{
	// TODO: добавьте свой код обработчика уведомлений
	diffusModel = RadioDiffuselModel.GetCheck();
}
void CChangeParemetersDialog::OnBnClickedMirrorModel()
{
	diffusModel = !(MirrorModel.GetCheck());
	// TODO: добавьте свой код обработчика уведомлений
}
bool CChangeParemetersDialog::isModelDiffusial() {
	return diffusModel;
}




void CChangeParemetersDialog::OnBnClickedMfccolorbutton1()
{
	ChangedColor = ColorSelect.GetColor();
	// TODO: добавьте свой код обработчика уведомлений
	bifColorchanged = true;
}
COLORREF CChangeParemetersDialog::GetChangedColor()
{
	return ChangedColor;
}
bool CChangeParemetersDialog::ifColorchanged() {
	return ChangedColor;
}

