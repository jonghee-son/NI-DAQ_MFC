
// 2019130023_SJH.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy2019130023SJHApp:
// See 2019130023_SJH.cpp for the implementation of this class
//

class CMy2019130023SJHApp : public CWinApp
{
public:
	CMy2019130023SJHApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy2019130023SJHApp theApp;
