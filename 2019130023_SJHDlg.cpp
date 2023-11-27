
// 2019130023_SJHDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "2019130023_SJH.h"
#include "2019130023_SJHDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy2019130023SJHDlg dialog



CMy2019130023SJHDlg::CMy2019130023SJHDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY2019130023_SJH_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_pWndShow = NULL;
}

void CMy2019130023SJHDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_CTL, m_tabCtl);
}

BEGIN_MESSAGE_MAP(CMy2019130023SJHDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_CTL, &CMy2019130023SJHDlg::OnTcnSelchangeTabCtl)
END_MESSAGE_MAP()


// CMy2019130023SJHDlg message handlers

BOOL CMy2019130023SJHDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_tabCtl.InsertItem(0, _T("디지털 I/O"), 0);
	m_tabCtl.InsertItem(1, _T("아날로그 I/O"), 1);

	CRect Rect;
	m_tabCtl.GetClientRect(&Rect);
	m_dlgDigitalIO.Create(IDD_DIGITALIO_DLG, &m_tabCtl);
	m_dlgDigitalIO.SetWindowPos(NULL, 5, 25, Rect.Width() - 10, Rect.Height() - 30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_pWndShow = &m_dlgDigitalIO;

	m_tabCtl.GetClientRect(&Rect);
	m_dlgAnalogIO.Create(IDD_ANALOGIO_DLG, &m_tabCtl);
	m_dlgAnalogIO.SetWindowPos(NULL, 5, 25, Rect.Width() - 10, Rect.Height() - 30, SWP_HIDEWINDOW | SWP_NOZORDER);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy2019130023SJHDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy2019130023SJHDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy2019130023SJHDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy2019130023SJHDlg::OnTcnSelchangeTabCtl(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here
	if (m_pWndShow != NULL)
	{
		m_pWndShow->ShowWindow(SW_HIDE);
		m_pWndShow = NULL;
	}
	int nIndex = m_tabCtl.GetCurSel();
	switch (nIndex)
	{
	case 0:
		m_dlgDigitalIO.ShowWindow(SW_SHOW);
		m_pWndShow = &m_dlgDigitalIO;
		break;
	case 1:
		m_dlgAnalogIO.ShowWindow(SW_SHOW);
		m_pWndShow = &m_dlgAnalogIO;
		break;
	}
	*pResult = 0;
}
