
// 2019130023_SJHDlg.h : header file
//

#pragma once
#include "DlgDigitalIO.h"
#include "CDlgAnalogIO.h"


// CMy2019130023SJHDlg dialog
class CMy2019130023SJHDlg : public CDialogEx
{
// Construction
public:
	CMy2019130023SJHDlg(CWnd* pParent = nullptr);	// standard constructor

	CDlgDigitalIO m_dlgDigitalIO;
	CDlgAnalogIO m_dlgAnalogIO;
	CWnd* m_pWndShow;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2019130023_SJH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tabCtl;
	afx_msg void OnTcnSelchangeTabCtl(NMHDR* pNMHDR, LRESULT* pResult);
};
