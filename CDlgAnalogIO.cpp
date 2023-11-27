// CDlgAnalogIO.cpp : implementation file
//
#pragma warning(disable:4996)

#include "pch.h"
#include "2019130023_SJH.h"
#include "afxdialogex.h"
#include "CDlgAnalogIO.h"


// CDlgAnalogIO dialog

IMPLEMENT_DYNAMIC(CDlgAnalogIO, CDialogEx)

CDlgAnalogIO::CDlgAnalogIO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ANALOGIO_DLG, pParent)
{
	m_bThreadSt = TRUE;
	m_pThread = NULL;
	m_strFileName = _T("");
	m_bFileSaveChk = FALSE;

	m_bSaveBtnSt = FALSE;
}

CDlgAnalogIO::~CDlgAnalogIO()
{
}

void CDlgAnalogIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_IN_PORT, m_cmbInPort);
	DDX_Control(pDX, IDC_ST_SEG, m_stSeg);
	DDX_Control(pDX, IDC_ST_METER, m_stMeter);
}


BEGIN_MESSAGE_MAP(CDlgAnalogIO, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_IN_START, &CDlgAnalogIO::OnBnClickedBtnInStart)
	ON_BN_CLICKED(IDC_BTN_IN_STOP, &CDlgAnalogIO::OnBnClickedBtnInStop)
	ON_BN_CLICKED(IDC_BTN_TH_START, &CDlgAnalogIO::OnBnClickedBtnThStart)
	ON_BN_CLICKED(IDC_BTN_TH_STOP, &CDlgAnalogIO::OnBnClickedBtnThStop)
	ON_BN_CLICKED(IDC_BTN_TI_START, &CDlgAnalogIO::OnBnClickedBtnTiStart)
	ON_BN_CLICKED(IDC_BTN_TI_STOP, &CDlgAnalogIO::OnBnClickedBtnTiStop)
	ON_BN_CLICKED(IDC_BTN_SAVE_START, &CDlgAnalogIO::OnBnClickedBtnSaveStart)
	ON_BN_CLICKED(IDC_BTN_SAVE_STOP, &CDlgAnalogIO::OnBnClickedBtnSaveStop)
END_MESSAGE_MAP()


// CDlgAnalogIO message handlers


bool CDlgAnalogIO::DAQmxErrChk(int nErr)
{
	// TODO: Add your implementation code here.
	char errBuff[2048] = { '\0' };
	if (DAQmxFailed(nErr)) {
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
		AfxMessageBox((LPCTSTR)errBuff, MB_OK, NULL);
		return FALSE;
	}

	return TRUE;
}


void CDlgAnalogIO::GetAnalogInput()
{
	// TODO: Add your implementation code here.
	float64 m_fInputVal;

	DAQmxReadAnalogScalarF64(m_taskInPort, 10.0, &m_fInputVal, NULL);

	m_stSeg.SetPos((float)m_fInputVal, true, 0.10);
	m_stMeter.UpdateNeedle((double)m_fInputVal);
	m_InGraphCtrl.AppendPoint((double)m_fInputVal);

	if (m_bFileSaveChk == TRUE) {
		SetSaveData((double)m_fInputVal);
	}
}


CString CDlgAnalogIO::GetFileName()
{
	// TODO: Add your implementation code here.
	char Path[MAX_PATH] = { 0x00, };
	char sDirectory[1000] = { 0x00, };
	CString str = _T("");
	int nTime[7] = { 0, };

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	nTime[0] = systime.wYear;
	nTime[1] = systime.wMonth;
	nTime[2] = systime.wDay;
	nTime[3] = systime.wHour;
	nTime[4] = systime.wMinute;
	nTime[5] = systime.wSecond;
	nTime[6] = systime.wMilliseconds;
	
	str.Format(_T("%04d%02d%02d_%02d%02d%02d%03d.txt"), nTime[0], nTime[1], nTime[2], nTime[3], nTime[4], nTime[5], nTime[6]);

	GetModuleFileName(NULL, Path, 1024);
	CString strTmp;
	CString strPath = Path;
	strPath = strPath.Left(strPath.ReverseFind('\\'));
	strcpy(Path, strPath + _T("\\") + str);
	strncpy(sDirectory, Path, strlen(Path));

	return sDirectory;
}


void CDlgAnalogIO::SetSaveData(double bVal)
{
	// TODO: Add your implementation code here.
	int nLen = 0;
	FILE* src;
	CString str = "";
	int nTime[7] = { 0, };

	SYSTEMTIME systime;
	GetLocalTime(&systime);
	nTime[0] = systime.wYear;
	nTime[1] = systime.wMonth;
	nTime[2] = systime.wDay;
	nTime[3] = systime.wHour;
	nTime[4] = systime.wMinute;
	nTime[5] = systime.wSecond;
	nTime[6] = systime.wMilliseconds;
	str.Format(_T("%02d:%02d:%02d:%03d"), nTime[3], nTime[4], nTime[5], nTime[6]);

	char sDataBody[500] = { 0, };
	char sDataHeader[255] = { 0, };

	src = fopen(m_strFileName, _T("a"));
	strcpy(sDataBody, str);
	strcat(sDataBody, _T("    "));
	str.Format(_T("%5.2f"), bVal);
	strcat(sDataBody, str);
	strcat(sDataBody, _T("\n"));

	if (src != NULL) {
		nLen = strlen(sDataBody);
		fwrite(sDataBody, 1, nLen, src);
		fclose(src);
	}
}


void CDlgAnalogIO::SetAnalogInputBtnEnable(int nVal)
{
	// TODO: Add your implementation code here.
	switch (nVal) {
	case 0:
		m_cmbInPort.EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TH_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TH_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TI_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TI_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE_STOP)->EnableWindow(FALSE);
		break;
	case 1:
		m_cmbInPort.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_TH_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_TH_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TI_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_TI_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE_STOP)->EnableWindow(FALSE);
		break;
	case 2:
		m_cmbInPort.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TH_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TH_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_TI_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TI_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_SAVE_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SAVE_STOP)->EnableWindow(FALSE);
		break;
	case 3:
		m_cmbInPort.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TH_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TH_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TI_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_TI_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SAVE_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_SAVE_STOP)->EnableWindow(FALSE);
		break;
	}
}

UINT ThreadAnalogInputFunc(LPVOID pParam)
{
	CDlgAnalogIO* pAnalogIO = (CDlgAnalogIO*)pParam;

	while (pAnalogIO->m_bThreadSt) {
		pAnalogIO->GetAnalogInput();
	}

	pAnalogIO->m_pThread = NULL;
	return 0;
}


void CDlgAnalogIO::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	GetAnalogInput();

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CDlgAnalogIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	// Graph Control
	CRect rect;
	GetDlgItem(IDC_ST_IN_GRAPH)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_InGraphCtrl.Create(WS_VISIBLE | WS_CHILD, rect, this);
	m_InGraphCtrl.SetRange(0.0, 10.0, 1);
	m_InGraphCtrl.SetYUnits(_T("X축"));
	m_InGraphCtrl.SetXUnits(_T("Y축"));
	m_InGraphCtrl.SetBackgroundColor(RGB(0, 0, 64));
	m_InGraphCtrl.SetGridColor(RGB(192, 192, 255));
	m_InGraphCtrl.SetPlotColor(RGB(255, 255, 255));

	// Seven Segment Control
	m_stSeg.SetFormatString(_T("%.2f"));
	m_stSeg.SetBlankPadding(8);
	m_stSeg.SetColourFaded(RGB(40, 40, 40));
	m_stSeg.SetBarHeight();
	m_stSeg.SetColours(RGB(200, 200, 200), 0, RGB(150, 0, 0));

	// Meter Control
	m_stMeter.SetValueDecimals(2);
	m_stMeter.SetRange((double)0.0, (double)10.0);
	m_stMeter.SetScaleDecimals(2);
	m_stMeter.SetUnits((CString)_T(""));
	m_stMeter.SetNeedleColor(RGB(255, 0, 0));

	// Port ComboBox
	m_cmbInPort.AddString(_T("ai0"));
	m_cmbInPort.AddString(_T("ai1"));
	m_cmbInPort.AddString(_T("ai2"));
	m_cmbInPort.AddString(_T("ai3"));
	m_cmbInPort.AddString(_T("ai4"));
	m_cmbInPort.AddString(_T("ai5"));
	m_cmbInPort.AddString(_T("ai6"));
	m_cmbInPort.AddString(_T("ai7"));
	m_cmbInPort.AddString(_T("ai8"));
	m_cmbInPort.AddString(_T("ai9"));
	m_cmbInPort.AddString(_T("ai10"));
	m_cmbInPort.AddString(_T("ai11"));
	m_cmbInPort.AddString(_T("ai12"));
	m_cmbInPort.AddString(_T("ai13"));
	m_cmbInPort.AddString(_T("ai14"));
	m_cmbInPort.AddString(_T("ai15"));
	m_cmbInPort.SetCurSel(0);

	m_taskInPort = 0;
	m_stSeg.SetPos((float)0.0, true, 0.10);

	// Button
	SetAnalogInputBtnEnable(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgAnalogIO::OnBnClickedBtnInStart()
{
	// TODO: Add your control notification handler code here
	SetAnalogInputBtnEnable(1);

	int32 terminalConfig = DAQmx_Val_RSE;
	float64 minVal = -10.0, maxVal = 10.0;

	int nError = 0;
	if (!m_taskInPort) {
		m_InGraphCtrl.Reset();

		DAQmxErrChk(nError = DAQmxCreateTask("", &m_taskInPort));

		CString strAI01, strAI02;
		strAI01.Format(_T("Dev1/ai%d"), m_cmbInPort.GetCurSel());
		strAI02.Format(_T("AI%d"), m_cmbInPort.GetCurSel());

		DAQmxErrChk(nError = DAQmxCreateAIVoltageChan(m_taskInPort, strAI01, strAI02, terminalConfig, minVal, maxVal, DAQmx_Val_Volts, ""));

		DAQmxErrChk(nError = DAQmxStartTask(m_taskInPort));
	}
}


void CDlgAnalogIO::OnBnClickedBtnInStop()
{
	// TODO: Add your control notification handler code here
	SetAnalogInputBtnEnable(0);

	if (m_taskInPort != 0) {
		DAQmxStopTask(m_taskInPort);
		DAQmxClearTask(m_taskInPort);
		m_taskInPort = 0;
	}
}


void CDlgAnalogIO::OnBnClickedBtnThStart()
{
	// TODO: Add your control notification handler code here
	SetAnalogInputBtnEnable(2);

	m_bThreadSt = TRUE;
	m_pThread = AfxBeginThread(ThreadAnalogInputFunc, this);
}


void CDlgAnalogIO::OnBnClickedBtnThStop()
{
	// TODO: Add your control notification handler code here
	if (m_bSaveBtnSt == TRUE) {
		AfxMessageBox(_T("먼저 데이터 저장을 정지해 주세요!"), MB_OK);
		return;
	}

	SetAnalogInputBtnEnable(1);

	m_bThreadSt = FALSE;
}


void CDlgAnalogIO::OnBnClickedBtnTiStart()
{
	// TODO: Add your control notification handler code here
	SetAnalogInputBtnEnable(3);

	SetTimer(1, 100, NULL);
}


void CDlgAnalogIO::OnBnClickedBtnTiStop()
{
	// TODO: Add your control notification handler code here
	if (m_bSaveBtnSt == TRUE) {
		AfxMessageBox(_T("먼저 데이터 저장을 정지해 주세요!"), MB_OK);
		return;
	}

	SetAnalogInputBtnEnable(1);
	KillTimer(1);
}


void CDlgAnalogIO::OnBnClickedBtnSaveStart()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTN_SAVE_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SAVE_STOP)->EnableWindow(TRUE);

	m_bFileSaveChk = TRUE;
	m_strFileName = GetFileName();
	m_bSaveBtnSt = TRUE;
}


void CDlgAnalogIO::OnBnClickedBtnSaveStop()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_BTN_SAVE_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SAVE_STOP)->EnableWindow(FALSE);

	m_bFileSaveChk = FALSE;
	m_bSaveBtnSt = FALSE;
}
