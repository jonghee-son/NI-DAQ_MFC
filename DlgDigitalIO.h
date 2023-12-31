#pragma once
#include "afxdialogex.h"
#include <NIDAQmx.h>


// CDlgDigitalIO dialog
#define MAX_TIMEOUT 5.0

class CDlgDigitalIO : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDigitalIO)

public:
	CDlgDigitalIO(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgDigitalIO();

	int m_nSwitchSt[8];
	CStatic* m_pswTog[8];
	CEdit* m_pstOut[8];
	CBitmapButton* m_pswPush[8];

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIGITALIO_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	TaskHandle m_taskOutPort;
	bool DAQmxErrChk(int nErr);
	void SetDigitalOutputValue(int nNo, int nVal);
	void SetDigitalOutputBtnEnable(int nVal);
	CBitmapButton m_swPush0;
	CBitmapButton m_swPush1;
	CBitmapButton m_swPush2;
	CBitmapButton m_swPush3;
	CBitmapButton m_swPush4;
	CBitmapButton m_swPush5;
	CBitmapButton m_swPush6;
	CBitmapButton m_swPush7;
	afx_msg void OnBnClickedBtnOutStart();
	afx_msg void OnBnClickedBtnOutStop();
	afx_msg void OnBnClickedBtnOutHigh();
	afx_msg void OnBnClickedBtnOutLow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CStatic m_swTog0;
	CStatic m_swTog1;
	CStatic m_swTog2;
	CStatic m_swTog3;
	CStatic m_swTog4;
	CStatic m_swTog5;
	CStatic m_swTog6;
	CStatic m_swTog7;
	afx_msg void OnStnClickedSwTog0();
	afx_msg void OnStnClickedSwTog1();
	afx_msg void OnStnClickedSwTog2();
	afx_msg void OnStnClickedSwTog3();
	afx_msg void OnStnClickedSwTog4();
	afx_msg void OnStnClickedSwTog5();
	afx_msg void OnStnClickedSwTog6();
	afx_msg void OnStnClickedSwTog7();
	CComboBox m_cmbOutPort;
	CEdit m_stOut0;
	CEdit m_stOut1;
	CEdit m_stOut2;
	CEdit m_stOut3;
	CEdit m_stOut4;
	CEdit m_stOut5;
	CEdit m_stOut6;
	CEdit m_stOut7;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnInStart();
	afx_msg void OnBnClickedBtnInStop();
	afx_msg void OnBnClickedBtnInRead();
	afx_msg void OnBnClickedBtnInTiStart();
	afx_msg void OnBnClickedBtnInTiStop();
	afx_msg void OnBnClickedBtnInThStart();
	afx_msg void OnBnClickedBtnInThStop();
	CComboBox m_cmbInPort;
	CEdit m_stIn0;
	CEdit m_stIn1;
	CEdit m_stIn2;
	CEdit m_stIn3;
	CEdit m_stIn4;
	CEdit m_stIn5;
	CEdit m_stIn6;
	CEdit m_stIn7;
	CStatic m_Led0;
	CStatic m_Led1;
	CStatic m_Led2;
	CStatic m_Led3;
	CStatic m_Led4;
	CStatic m_Led5;
	CStatic m_Led6;
	CStatic m_Led7;
	TaskHandle m_taskInPort;
	CEdit *m_pstIn[8];
	CStatic *m_pLed[8];
	BOOL m_bThreadSt;
	CWinThread * m_pThread;
	int m_nBeforeData;
	void GetDigitalInputRead();
	void SetDigitalInputBtnEnable(int nVal);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

UINT ThreadDigitalInputFunc(LPVOID pParam);
