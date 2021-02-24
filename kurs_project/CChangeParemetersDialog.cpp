//приложение 1
#include "pch.h"
#include "kurs_project.h"
#include "CChangeParemetersDialog.h"
#include "afxdialogex.h"
IMPLEMENT_DYNAMIC(CChangeParemetersDialog, CDialogEx)
CChangeParemetersDialog::CChangeParemetersDialog(CWnd* pParent )
	: CDialogEx(IDD_PARAMETER_CHANGE_DIALOG, pParent){}
CChangeParemetersDialog::~CChangeParemetersDialog(){}
void CChangeParemetersDialog::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_R_BIG_INPUT, Big_R_input);
	DDX_Control(pDX, IDC_R_LITTLE_INPUT, R_LITTLE_INPUT);
	DDX_Control(pDX, IDC_LIGHT_FI, LightFi);
	DDX_Control(pDX, IDC_LIGHT_THETA, LightTheta);
	DDX_Control(pDX, IDC_WATCHER_FI, WatcherFi);
	DDX_Control(pDX, IDC_WATCHER_THETA, WatcherTheta);
	DDX_Control(pDX, IDC_DIFFUSE_MODEL, RadioDiffuselModel);
	DDX_Control(pDX, IDD_MIRROR_MODEL, MirrorModel);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, ColorSelect);}
BEGIN_MESSAGE_MAP(CChangeParemetersDialog, CDialogEx)	
	ON_BN_CLICKED(IDOK, &CChangeParemetersDialog::OnBnClickedOk)
	ON_EN_CHANGE(IDC_R_BIG_INPUT, &CChangeParemetersDialog::OnEnChangeRBigInput)
	ON_EN_CHANGE(IDC_R_LITTLE_INPUT, &CChangeParemetersDialog::OnEnChangeRLittleInput)
	ON_EN_CHANGE(IDC_LIGHT_FI, &CChangeParemetersDialog::OnEnChangeLightFi)
	ON_EN_CHANGE(IDC_LIGHT_THETA, &CChangeParemetersDialog::OnEnChangeLightTheta)
	ON_EN_CHANGE(IDC_WATCHER_FI, &CChangeParemetersDialog::OnEnChangeWatcherFi)
	ON_EN_CHANGE(IDC_WATCHER_THETA, &CChangeParemetersDialog::OnEnChangeWatcherTheta)
	ON_BN_CLICKED(IDC_DIFFUSE_MODEL, &CChangeParemetersDialog::OnBnClickedDiffuseModel)
	ON_BN_CLICKED(IDD_MIRROR_MODEL, &CChangeParemetersDialog::OnBnClickedMirrorModel)
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CChangeParemetersDialog::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()
int returnNormalAngle(int angleIn) {
	int angle = angleIn;
	if (angle >= 360)
	{
		angle -= 360;
		angle = returnNormalAngle(angle);
	}
	return angle;}
void CChangeParemetersDialog::OnBnClickedOk(){	CDialogEx::OnOK();}
void CChangeParemetersDialog::OnEnChangeRBigInput(){
	CString* s = new CString();
	Big_R_input.GetWindowText(*s);
	CString input = *s;
	try {
		R = _ttoi(input);
		Rchanged = true;
	}
	catch (...) {	}}
int CChangeParemetersDialog::GetR() {return R;}
bool CChangeParemetersDialog::ifRchanged() {return Rchanged;}
void CChangeParemetersDialog::OnEnChangeRLittleInput(){
	CString* s = new CString();
	R_LITTLE_INPUT.GetWindowText(*s);
	CString input = *s;
	try {
		r = _ttoi(input);
		rchanged = true;
	}
	catch (...)	{}}
int CChangeParemetersDialog::Getr() {return r;}
bool CChangeParemetersDialog::ifrchanged() {return rchanged;}
void CChangeParemetersDialog::OnEnChangeLightFi(){
	CString* s = new CString();
	LightFi.GetWindowText(*s);
	CString input = *s;
	try {
		iLightFi = _ttoi(input);
		iLightFi = returnNormalAngle(iLightFi);
		bifLightFichanged = true;
	}
	catch (...)	{	}}
int CChangeParemetersDialog::GetLightFi() {	return iLightFi;}
bool CChangeParemetersDialog::ifLightFichanged() {
	return bifLightFichanged;}
void CChangeParemetersDialog::OnEnChangeLightTheta(){
	CString* s = new CString();
	LightTheta.GetWindowText(*s);
	CString input = *s;
	try {
		iLightTheta = _ttoi(input);
		iLightTheta = returnNormalAngle(iLightTheta);
		bifLightThetachanged = true;
	}
	catch (...)	{	}}
int CChangeParemetersDialog::GetLightTheta() {return iLightTheta;}
bool CChangeParemetersDialog::ifLightThetachanged() {return bifLightThetachanged;}
void CChangeParemetersDialog::OnEnChangeWatcherFi(){
	CString* s = new CString();
	WatcherFi.GetWindowText(*s);
	CString input = *s;
	try {
		iWatcherFi = _ttoi(input);
		iWatcherFi = returnNormalAngle(iWatcherFi);

		bifWatcherFichanged = true;
	}
	catch (...)	{	}}
int CChangeParemetersDialog::GetWatcherFi() {return iWatcherFi;}
bool CChangeParemetersDialog::ifWatcherFichanged() {return bifWatcherFichanged;}
void CChangeParemetersDialog::OnEnChangeWatcherTheta(){
	CString* s = new CString();
	WatcherTheta.GetWindowText(*s);
	CString input = *s;
	try {
		iWatcherTheta = _ttoi(input);
		iWatcherTheta = returnNormalAngle(iWatcherTheta);

		bifWatcherThetachanged = true;
	}
	catch (...)	{	}}
int CChangeParemetersDialog::GetWatcherTheta() {return iWatcherTheta;}
bool CChangeParemetersDialog::ifWatcherThetachanged() {	return bifWatcherThetachanged;}
void CChangeParemetersDialog::OnBnClickedDiffuseModel(){
	diffusModel = RadioDiffuselModel.GetCheck();
	bisModelChanged = true;}
void CChangeParemetersDialog::OnBnClickedMirrorModel(){
	diffusModel = !(MirrorModel.GetCheck());
	bisModelChanged = true;}
bool CChangeParemetersDialog::isModelDiffusial() {return diffusModel;}
bool CChangeParemetersDialog::ifModelChanged() {return bisModelChanged;}
void CChangeParemetersDialog::OnBnClickedMfccolorbutton1(){
	ChangedColor = ColorSelect.GetColor();
	bifColorchanged = true;}
COLORREF CChangeParemetersDialog::GetChangedColor(){return ChangedColor;}
bool CChangeParemetersDialog::ifColorchanged() {return ChangedColor;}