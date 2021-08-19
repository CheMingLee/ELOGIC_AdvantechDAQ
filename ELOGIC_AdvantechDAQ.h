#pragma once

#ifndef __AFXWIN_H__
	#error "對 PCH 包含此檔案前先包含 'stdafx.h'"
#endif

#include "resource.h"
// Advantech Automation.BDaq
#include "bdaqctrl.h"
using namespace Automation::BDaq;

// DLL export
#define DllExport __declspec(dllexport)

// CELOGIC_AdvantechDAQApp
class CELOGIC_AdvantechDAQApp : public CWinApp
{
public:
	CELOGIC_AdvantechDAQApp();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};
