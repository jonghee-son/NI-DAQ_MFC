#pragma once
#include "afxdialogex.h"
#include <NIDAQmx.h>
#include "OScopeCtrl.h"
#include "StaticCounter.h"
#include "3DMeterCtrl.h"


// CDlgAnalogIO dialog

class CDlgAnalogIO : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAnalogIO)

public:
	CDlgAnalogIO(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgAnalogIO();

	BOOL m_bThreadSt;
	CWinThread* m_pThread;
	COScopeCtrl m_InGraphCtrl;
	TaskHandle m_taskInPort;

	BOOL m_bSaveBtnSt;
	BOOL m_bFileSaveChk;
	CString m_strFileName;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ANALOGIO_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool DAQmxErrChk(int nErr);
	void GetAnalogInput();
	CString GetFileName();
	void SetSaveData(double bVal);
	void SetAnalogInputBtnEnable(int nVal);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnInStart();
	afx_msg void OnBnClickedBtnInStop();
	afx_msg void OnBnClickedBtnThStart();
	afx_msg void OnBnClickedBtnThStop();
	afx_msg void OnBnClickedBtnTiStart();
	afx_msg void OnBnClickedBtnTiStop();
	afx_msg void OnBnClickedBtnSaveStart();
	afx_msg void OnBnClickedBtnSaveStop();
	CComboBox m_cmbInPort;
	CStaticCounter m_stSeg;
	C3DMeterCtrl m_stMeter;
};
