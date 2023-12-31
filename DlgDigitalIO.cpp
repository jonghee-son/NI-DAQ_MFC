// DlgDigitalIO.cpp : implementation file
//

#include "pch.h"
#include "2019130023_SJH.h"
#include "afxdialogex.h"
#include "DlgDigitalIO.h"


// CDlgDigitalIO dialog

IMPLEMENT_DYNAMIC(CDlgDigitalIO, CDialogEx)

CDlgDigitalIO::CDlgDigitalIO(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIGITALIO_DLG, pParent)
{
	for (int i = 0; i < 8; i++) {
		m_nSwitchSt[i] = 0;
	}

	m_pswTog[0] = &m_swTog0;
	m_pswTog[1] = &m_swTog1;
	m_pswTog[2] = &m_swTog2;
	m_pswTog[3] = &m_swTog3;
	m_pswTog[4] = &m_swTog4;
	m_pswTog[5] = &m_swTog5;
	m_pswTog[6] = &m_swTog6;
	m_pswTog[7] = &m_swTog7;

	m_pstOut[0] = &m_stOut0;
	m_pstOut[1] = &m_stOut1;
	m_pstOut[2] = &m_stOut2;
	m_pstOut[3] = &m_stOut3;
	m_pstOut[4] = &m_stOut4;
	m_pstOut[5] = &m_stOut5;
	m_pstOut[6] = &m_stOut6;
	m_pstOut[7] = &m_stOut7;

	m_taskOutPort = 0;
	m_pswPush[0] = &m_swPush0;
	m_pswPush[1] = &m_swPush1;
	m_pswPush[2] = &m_swPush2;
	m_pswPush[3] = &m_swPush3;
	m_pswPush[4] = &m_swPush4;
	m_pswPush[5] = &m_swPush5;
	m_pswPush[6] = &m_swPush6;
	m_pswPush[7] = &m_swPush7;

	m_bThreadSt = TRUE;
	m_nBeforeData = 0;

	m_pstIn[0] = &m_stIn0;
	m_pstIn[1] = &m_stIn1;
	m_pstIn[2] = &m_stIn2;
	m_pstIn[3] = &m_stIn3;
	m_pstIn[4] = &m_stIn4;
	m_pstIn[5] = &m_stIn5;
	m_pstIn[6] = &m_stIn6;
	m_pstIn[7] = &m_stIn7;

	m_pLed[0] = &m_Led0;
	m_pLed[1] = &m_Led1;
	m_pLed[2] = &m_Led2;
	m_pLed[3] = &m_Led3;
	m_pLed[4] = &m_Led4;
	m_pLed[5] = &m_Led5;
	m_pLed[6] = &m_Led6;
	m_pLed[7] = &m_Led7;

	m_taskInPort = 0;
	m_pThread = NULL;
}

CDlgDigitalIO::~CDlgDigitalIO()
{
}

void CDlgDigitalIO::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SW_PUSH_0, m_swPush0);
	DDX_Control(pDX, IDC_SW_PUSH_1, m_swPush1);
	DDX_Control(pDX, IDC_SW_PUSH_2, m_swPush2);
	DDX_Control(pDX, IDC_SW_PUSH_3, m_swPush3);
	DDX_Control(pDX, IDC_SW_PUSH_4, m_swPush4);
	DDX_Control(pDX, IDC_SW_PUSH_5, m_swPush5);
	DDX_Control(pDX, IDC_SW_PUSH_6, m_swPush6);
	DDX_Control(pDX, IDC_SW_PUSH_7, m_swPush7);
	DDX_Control(pDX, IDC_SW_TOG0, m_swTog0);
	DDX_Control(pDX, IDC_SW_TOG1, m_swTog1);
	DDX_Control(pDX, IDC_SW_TOG2, m_swTog2);
	DDX_Control(pDX, IDC_SW_TOG3, m_swTog3);
	DDX_Control(pDX, IDC_SW_TOG4, m_swTog4);
	DDX_Control(pDX, IDC_SW_TOG5, m_swTog5);
	DDX_Control(pDX, IDC_SW_TOG6, m_swTog6);
	DDX_Control(pDX, IDC_SW_TOG7, m_swTog7);
	DDX_Control(pDX, IDC_CMB_OUT_PORT, m_cmbOutPort);
	DDX_Control(pDX, IDC_ST_OUT0, m_stOut0);
	DDX_Control(pDX, IDC_ST_OUT1, m_stOut1);
	DDX_Control(pDX, IDC_ST_OUT2, m_stOut2);
	DDX_Control(pDX, IDC_ST_OUT3, m_stOut3);
	DDX_Control(pDX, IDC_ST_OUT4, m_stOut4);
	DDX_Control(pDX, IDC_ST_OUT5, m_stOut5);
	DDX_Control(pDX, IDC_ST_OUT6, m_stOut6);
	DDX_Control(pDX, IDC_ST_OUT7, m_stOut7);
	DDX_Control(pDX, IDC_CMB_IN_PORT, m_cmbInPort);
	DDX_Control(pDX, IDC_ST_IN0, m_stIn0);
	DDX_Control(pDX, IDC_ST_IN1, m_stIn1);
	DDX_Control(pDX, IDC_ST_IN2, m_stIn2);
	DDX_Control(pDX, IDC_ST_IN3, m_stIn3);
	DDX_Control(pDX, IDC_ST_IN4, m_stIn4);
	DDX_Control(pDX, IDC_ST_IN5, m_stIn5);
	DDX_Control(pDX, IDC_ST_IN6, m_stIn6);
	DDX_Control(pDX, IDC_ST_IN7, m_stIn7);
	DDX_Control(pDX, IDC_LED0, m_Led0);
	DDX_Control(pDX, IDC_LED1, m_Led1);
	DDX_Control(pDX, IDC_LED2, m_Led2);
	DDX_Control(pDX, IDC_LED3, m_Led3);
	DDX_Control(pDX, IDC_LED4, m_Led4);
	DDX_Control(pDX, IDC_LED5, m_Led5);
	DDX_Control(pDX, IDC_LED6, m_Led6);
	DDX_Control(pDX, IDC_LED7, m_Led7);
}


BEGIN_MESSAGE_MAP(CDlgDigitalIO, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_OUT_START, &CDlgDigitalIO::OnBnClickedBtnOutStart)
	ON_BN_CLICKED(IDC_BTN_OUT_STOP, &CDlgDigitalIO::OnBnClickedBtnOutStop)
	ON_BN_CLICKED(IDC_BTN_OUT_HIGH, &CDlgDigitalIO::OnBnClickedBtnOutHigh)
	ON_BN_CLICKED(IDC_BTN_OUT_LOW, &CDlgDigitalIO::OnBnClickedBtnOutLow)
	ON_STN_CLICKED(IDC_SW_TOG0, &CDlgDigitalIO::OnStnClickedSwTog0)
	ON_STN_CLICKED(IDC_SW_TOG1, &CDlgDigitalIO::OnStnClickedSwTog1)
	ON_STN_CLICKED(IDC_SW_TOG2, &CDlgDigitalIO::OnStnClickedSwTog2)
	ON_STN_CLICKED(IDC_SW_TOG3, &CDlgDigitalIO::OnStnClickedSwTog3)
	ON_STN_CLICKED(IDC_SW_TOG4, &CDlgDigitalIO::OnStnClickedSwTog4)
	ON_STN_CLICKED(IDC_SW_TOG5, &CDlgDigitalIO::OnStnClickedSwTog5)
	ON_STN_CLICKED(IDC_SW_TOG6, &CDlgDigitalIO::OnStnClickedSwTog6)
	ON_STN_CLICKED(IDC_SW_TOG7, &CDlgDigitalIO::OnStnClickedSwTog7)
	ON_BN_CLICKED(IDC_BTN_IN_START, &CDlgDigitalIO::OnBnClickedBtnInStart)
	ON_BN_CLICKED(IDC_BTN_IN_STOP, &CDlgDigitalIO::OnBnClickedBtnInStop)
	ON_BN_CLICKED(IDC_BTN_IN_READ, &CDlgDigitalIO::OnBnClickedBtnInRead)
	ON_BN_CLICKED(IDC_BTN_IN_TI_START, &CDlgDigitalIO::OnBnClickedBtnInTiStart)
	ON_BN_CLICKED(IDC_BTN_IN_TI_STOP, &CDlgDigitalIO::OnBnClickedBtnInTiStop)
	ON_BN_CLICKED(IDC_BTN_IN_TH_START, &CDlgDigitalIO::OnBnClickedBtnInThStart)
	ON_BN_CLICKED(IDC_BTN_IN_TH_STOP, &CDlgDigitalIO::OnBnClickedBtnInThStop)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgDigitalIO message handlers


bool CDlgDigitalIO::DAQmxErrChk(int nErr)
{
	// TODO: Add your implementation code here.
	char errBuff[2048] = { '\0' };
	if (DAQmxFailed(nErr)) {
		DAQmxGetExtendedErrorInfo(errBuff, 2048);
		AfxMessageBox((LPCTSTR)errBuff, MB_OK, NULL);
		return false;
	}
	return true;
}


void CDlgDigitalIO::SetDigitalOutputValue(int nNo, int nVal)
{
	// TODO: Add your implementation code here.
	HANDLE h = NULL;
	h = m_pswTog[nNo]->GetBitmap();
	DeleteObject(h);

	if (nVal == 1) {
		h = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_TOG_ON));
		m_pstOut[nNo]->SetWindowText(_T("1"));
	} else {
		h = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_TOG_OFF));
		m_pstOut[nNo]->SetWindowText(_T("0"));
	}

	m_nSwitchSt[nNo] = nVal;
	m_pswTog[nNo]->SetBitmap((HBITMAP)h);

	uInt8 dataOutput[8];
	int32 sampsPerChanWritten;

	for (int i = 0; i < 8; i++) {
		dataOutput[i] = m_nSwitchSt[i];
	}

	DAQmxErrChk(DAQmxWriteDigitalLines(m_taskOutPort, 1, 1, MAX_TIMEOUT, DAQmx_Val_GroupByChannel, dataOutput, &sampsPerChanWritten, NULL));
}


void CDlgDigitalIO::SetDigitalOutputBtnEnable(int nVal)
{
	// TODO: Add your implementation code here.
	switch (nVal) {
	case 0:
		m_cmbOutPort.EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_0)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_1)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_2)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_3)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_4)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_5)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_6)->EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_7)->EnableWindow(FALSE);

		for (int i = 0; i < 8; i++) {
			m_pswTog[i]->EnableWindow(FALSE);
		}

		GetDlgItem(IDC_BTN_OUT_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OUT_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_OUT_HIGH)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_OUT_LOW)->EnableWindow(FALSE);

		break;
	case 1:
		m_cmbOutPort.EnableWindow(FALSE);
		GetDlgItem(IDC_SW_PUSH_0)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_1)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_2)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_3)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_4)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_5)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_6)->EnableWindow(TRUE);
		GetDlgItem(IDC_SW_PUSH_7)->EnableWindow(TRUE);

		for (int i = 0; i < 8; i++) {
			m_pswTog[i]->EnableWindow(TRUE);
		}

		GetDlgItem(IDC_BTN_OUT_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_OUT_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OUT_HIGH)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_OUT_LOW)->EnableWindow(TRUE);

		break;
	}
}


void CDlgDigitalIO::OnBnClickedBtnOutStart()
{
	// TODO: Add your control notification handler code here
	SetDigitalOutputBtnEnable(1);

	int nError;
	if (!m_taskOutPort) {
		DAQmxErrChk(nError = DAQmxCreateTask("", &m_taskOutPort));

		switch (m_cmbOutPort.GetCurSel()) {
		case 0:
			DAQmxErrChk(nError = DAQmxCreateDOChan(m_taskOutPort, "Dev1/port0/line0:7", "", DAQmx_Val_ChanForAllLines));
			break;
		case 1:
			DAQmxErrChk(nError = DAQmxCreateDOChan(m_taskOutPort, "Dev1/port1/line0:7", "", DAQmx_Val_ChanForAllLines));
			break;
		case 2:
			DAQmxErrChk(nError = DAQmxCreateDOChan(m_taskOutPort, "Dev1/port2/line0:7", "", DAQmx_Val_ChanForAllLines));
			break;
		}

		DAQmxErrChk(nError = DAQmxStartTask(m_taskOutPort));
	}
}


void CDlgDigitalIO::OnBnClickedBtnOutStop()
{
	// TODO: Add your control notification handler code here
	SetDigitalOutputBtnEnable(0);
	if (m_taskOutPort != 0) {
		DAQmxStopTask(m_taskOutPort);
		DAQmxClearTask(m_taskOutPort);
		m_taskOutPort = 0;
	}
}


void CDlgDigitalIO::OnBnClickedBtnOutHigh()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < 8; i++) {
		SetDigitalOutputValue(i, 1);
	}
}


void CDlgDigitalIO::OnBnClickedBtnOutLow()
{
	// TODO: Add your control notification handler code here
	for (int i = 0; i < 8; i++) {
		SetDigitalOutputValue(i, 0);
	}
}


BOOL CDlgDigitalIO::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	for (int i = 0; i < 8; i++) {
		if (m_pswPush[i]->GetSafeHwnd() == pMsg->hwnd) {
			if (pMsg->message == WM_LBUTTONDOWN) {
				SetDigitalOutputValue(i, 1);
			}
			else if (pMsg->message == WM_LBUTTONUP) {
				SetDigitalOutputValue(i, 0);
			}
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CDlgDigitalIO::OnStnClickedSwTog0()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[0] == 0) {
		SetDigitalOutputValue(0, 1);
	} else {
		SetDigitalOutputValue(0, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog1()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[1] == 0) {
		SetDigitalOutputValue(1, 1);
	} else {
		SetDigitalOutputValue(1, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog2()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[2] == 0) {
		SetDigitalOutputValue(2, 1);
	}
	else {
		SetDigitalOutputValue(2, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog3()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[3] == 0) {
		SetDigitalOutputValue(3, 1);
	}
	else {
		SetDigitalOutputValue(3, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog4()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[4] == 0) {
		SetDigitalOutputValue(4, 1);
	}
	else {
		SetDigitalOutputValue(4, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog5()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[5] == 0) {
		SetDigitalOutputValue(5, 1);
	}
	else {
		SetDigitalOutputValue(5, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog6()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[6] == 0) {
		SetDigitalOutputValue(6, 1);
	}
	else {
		SetDigitalOutputValue(6, 0);
	}
}


void CDlgDigitalIO::OnStnClickedSwTog7()
{
	// TODO: Add your control notification handler code here
	if (m_nSwitchSt[7] == 0) {
		SetDigitalOutputValue(7, 1);
	}
	else {
		SetDigitalOutputValue(7, 0);
	}
}


BOOL CDlgDigitalIO::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_swPush0.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush0.SizeToContent();
	m_swPush1.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush1.SizeToContent();
	m_swPush2.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush2.SizeToContent();
	m_swPush3.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush3.SizeToContent();
	m_swPush4.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush4.SizeToContent();
	m_swPush5.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush5.SizeToContent();
	m_swPush6.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush6.SizeToContent();
	m_swPush7.LoadBitmaps(IDB_BMP_PUSH_N, IDB_BMP_PUSH_S, 0, 0);
	m_swPush7.SizeToContent();

	for (int i = 0; i < 8; i++) {
		m_pstOut[i]->SetWindowText(_T("0"));
	}

	m_cmbOutPort.AddString(_T("port0"));
	m_cmbOutPort.AddString(_T("port1"));
	m_cmbOutPort.AddString(_T("port2"));
	m_cmbOutPort.SetCurSel(0);

	SetDigitalOutputBtnEnable(0);

	for (int i = 0; i < 8; i++) {
		m_pstIn[i]->SetWindowText(_T("0"));
	}

	m_cmbInPort.AddString(_T("port0"));
	m_cmbInPort.AddString(_T("port1"));
	m_cmbInPort.AddString(_T("port2"));
	m_cmbInPort.SetCurSel(0);

	SetDigitalInputBtnEnable(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgDigitalIO::OnBnClickedBtnInStart()
{
	// TODO: Add your control notification handler code here
	SetDigitalInputBtnEnable(1);

	int nError = 0;

	if (!m_taskInPort) {
		DAQmxErrChk(nError = DAQmxCreateTask("", &m_taskInPort));

		switch (m_cmbInPort.GetCurSel()) {
		case 0:
			DAQmxErrChk(nError = DAQmxCreateDIChan(m_taskInPort, "Dev1/port0/line0:7", "", DAQmx_Val_ChanForAllLines));
			break;
		case 1:
			DAQmxErrChk(nError = DAQmxCreateDIChan(m_taskInPort, "Dev1/port1/line0:7", "", DAQmx_Val_ChanForAllLines));
			break;
		case 2:
			DAQmxErrChk(nError = DAQmxCreateDIChan(m_taskInPort, "Dev1/port2/line0:7", "", DAQmx_Val_ChanForAllLines));
			break;
		}

		DAQmxErrChk(nError = DAQmxStartTask(m_taskInPort));
	}
}


void CDlgDigitalIO::OnBnClickedBtnInStop()
{
	// TODO: Add your control notification handler code here
	SetDigitalInputBtnEnable(0);

	if (m_taskInPort != 0) {
		DAQmxStopTask(m_taskInPort);
		DAQmxClearTask(m_taskInPort);
		m_taskInPort = 0;
	}
}


void CDlgDigitalIO::OnBnClickedBtnInRead()
{
	// TODO: Add your control notification handler code here
	GetDigitalInputRead();
}


void CDlgDigitalIO::OnBnClickedBtnInTiStart()
{
	// TODO: Add your control notification handler code here
	SetDigitalInputBtnEnable(3);
	SetTimer(1, 1000, NULL);
}


void CDlgDigitalIO::OnBnClickedBtnInTiStop()
{
	// TODO: Add your control notification handler code here
	SetDigitalInputBtnEnable(1);
	KillTimer(1);
}


void CDlgDigitalIO::OnBnClickedBtnInThStart()
{
	// TODO: Add your control notification handler code here
	SetDigitalInputBtnEnable(2);

	if (m_pThread == 0) {
		m_bThreadSt = TRUE;
		m_pThread = AfxBeginThread(ThreadDigitalInputFunc, this);
	}
}


void CDlgDigitalIO::OnBnClickedBtnInThStop()
{
	// TODO: Add your control notification handler code here
	SetDigitalInputBtnEnable(1);
	m_bThreadSt = FALSE;
}


void CDlgDigitalIO::GetDigitalInputRead()
{
	// TODO: Add your implementation code here.
	uInt32 arraySizeInSamps = 1;
	int32 sampsPerChanRead;
	uInt8 nReadData = 0;

	DAQmxErrChk(DAQmxReadDigitalU8(m_taskInPort, 1, 1.0, DAQmx_Val_GroupByChannel, &nReadData, arraySizeInSamps, &sampsPerChanRead, NULL));

	if (m_nBeforeData != nReadData) {
		m_nBeforeData = nReadData;
		int nVal[8] = { 0, };

		for (int i = 0; i < 8; i++) {
			if (i == 0) {
				nVal[0] = nReadData & 0x00000001;
			}
			else {
				nVal[i] = (nReadData >> i) & 0x00000001;
			}
		}

		HANDLE h;

		for (int i = 0; i < 8; i++) {
			h = NULL;
			h = m_pLed[i]->GetBitmap();
			DeleteObject(h);

			if (nVal[i] == 1) {
				h = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_LED_ON));
				m_pstIn[i]->SetWindowText(_T("1"));
			}
			else {
				h = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BMP_LED_OFF));
				m_pstIn[i]->SetWindowText(_T("0"));
			}
			m_pLed[i]->SetBitmap((HBITMAP)h);
		}
	}
}


void CDlgDigitalIO::SetDigitalInputBtnEnable(int nVal)
{
	// TODO: Add your implementation code here.
	switch (nVal) {
	case 0:
		m_cmbInPort.EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TH_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TH_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TI_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TI_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_READ)->EnableWindow(FALSE);
		break;
	case 1:
		m_cmbInPort.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_TH_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_TH_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TI_START)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_TI_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_READ)->EnableWindow(TRUE);
		break;
	case 2:
		m_cmbInPort.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TH_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TH_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_TI_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TI_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_READ)->EnableWindow(FALSE);
		break;
	case 3:
		m_cmbInPort.EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TH_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TH_STOP)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TI_START)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_IN_TI_STOP)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_IN_READ)->EnableWindow(FALSE);
		break;
	}

}

UINT ThreadDigitalInputFunc(LPVOID pParam) 
{
	CDlgDigitalIO* pDigitalIO = (CDlgDigitalIO*)pParam;

	while (pDigitalIO->m_bThreadSt) {
		pDigitalIO->GetDigitalInputRead();
	}

	pDigitalIO->m_pThread = NULL;
	return 0;
}


void CDlgDigitalIO::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == 1) {
		GetDigitalInputRead();
	}

	CDialogEx::OnTimer(nIDEvent);
}
