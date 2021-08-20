#include "stdafx.h"
#include "ELOGIC_AdvantechDAQ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Global
InstantAiCtrl *g_pInstantAiCtrl;
InstantDiCtrl *g_pInstantDiCtrl;
InstantDoCtrl *g_pInstantDoCtrl;
int g_iAiDevNum;
int g_iDioDevNum;

// CELOGIC_AdvantechDAQApp
BEGIN_MESSAGE_MAP(CELOGIC_AdvantechDAQApp, CWinApp)
END_MESSAGE_MAP()

CELOGIC_AdvantechDAQApp::CELOGIC_AdvantechDAQApp()
{
}

CELOGIC_AdvantechDAQApp theApp;

BOOL CELOGIC_AdvantechDAQApp::InitInstance()
{
	CWinApp::InitInstance();
	g_pInstantAiCtrl = InstantAiCtrl::Create();
	g_pInstantDiCtrl = InstantDiCtrl::Create();
	g_pInstantDoCtrl = InstantDoCtrl::Create();
	g_iAiDevNum = 0;
	g_iDioDevNum = 0;

	return TRUE;
}

int CELOGIC_AdvantechDAQApp::ExitInstance()
{
	g_pInstantAiCtrl->Dispose();
	g_pInstantDiCtrl->Dispose();
	g_pInstantDoCtrl->Dispose();

	return CWinApp::ExitInstance();
}

// DLL Function
DllExport void Set_DevNum(int iAiDevNum, int iDioDevNum)
{
	g_iAiDevNum = iAiDevNum;
	g_iDioDevNum = iDioDevNum;
}

DllExport double Read_AI(int iChanel)
{
	ErrorCode ret = Success;
	DeviceInformation devInfo(g_iAiDevNum);
	ret = g_pInstantAiCtrl->setSelectedDevice(devInfo);
	g_pInstantAiCtrl->getSelectedDevice(devInfo);
	if(BioFailed(ret))
		return 0;

	int32 ch = (int32)iChanel-1;
	double dataScaled = 0;

	ret = g_pInstantAiCtrl->Read(ch, dataScaled);
	if(BioFailed(ret))
		return 0;

	return dataScaled;
}

DllExport int Read_DI(int iDI_pin)
{
	ErrorCode ret = Success;
	DeviceInformation devInfo(g_iDioDevNum);
	ret = g_pInstantDiCtrl->setSelectedDevice(devInfo);
	g_pInstantDiCtrl->getSelectedDevice(devInfo);
	if(BioFailed(ret))
		return -1;

	int32 port = ((int32)iDI_pin-1) / 8;
	int32 bit = ((int32)iDI_pin-1) % 8;
	uint8 data = 0;
	ret = g_pInstantDiCtrl->ReadBit(port, bit, &data);
	if(BioFailed(ret))
		return -1;
	
	return (int)data;
}

DllExport bool Write_DO(int iDO_pin, int iOutData)
{
	ErrorCode ret = Success;
	DeviceInformation devInfo(g_iDioDevNum);
	ret = g_pInstantDoCtrl->setSelectedDevice(devInfo);
	g_pInstantDoCtrl->getSelectedDevice(devInfo);
	if(BioFailed(ret))
		return false;

	int32 port = ((int32)iDO_pin-1) / 8;
	int32 bit = ((int32)iDO_pin-1) % 8;
	uint8 data = 0;
	if (iOutData > 0)
		data = 1;
	
	ret = g_pInstantDoCtrl->WriteBit(port, bit, data);
	if(BioFailed(ret))
		return false;
	
	return true;
}
