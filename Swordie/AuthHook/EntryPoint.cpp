//---------------------------------------------------------------------------------------------
// Product	:	SwordieClient
// Version	:	Global MapleStory v176.1
// Authors	:	Rajan Grewal
// Date		:	February 3, 2020
// Notes	:	Must be injected via Swordie.exe
//---------------------------------------------------------------------------------------------

#include "Global.h"

Config*	g_pConfig = new Config();
DWORD	g_dwPID;


VOID WINAPI HeaderProc()
{
	Log("------------------------------------------------");
	Log("[Rajan] [%s] [v%s] [PID: %d]", OPT_APP_NAME, OPT_APP_VERSION, g_dwPID);
	Log("[Rajan]       \\    /\\  ");
	Log("[Rajan]        )  ( ')   ");
	Log("[Rajan]       (  /  )    ");
	Log("[Rajan] cat    \\(__)|   ");
	Log("[Rajan] [Built: %s]", __TIMESTAMP__);
	Log("------------------------------------------------");
}

VOID WINAPI ConfigProc()
{
	Log("[%s Config] Loading %s", OPT_APP_NAME, OPT_CFG_FILE);

	GetPrivateProfileStringA(OPT_CFG_NAME, "Host", "127.0.0.1", g_pConfig->szHostAddr, 255, OPT_CFG_FILE);
	Log("\t Host: %s", g_pConfig->szHostAddr);
	
	GetPrivateProfileStringA(OPT_CFG_NAME, "Proxy", "8.31.99.141", g_pConfig->szProxAddr, 255, OPT_CFG_FILE);
	Log("\t Proxy: %s", g_pConfig->szProxAddr);

	GetPrivateProfileStringA(OPT_CFG_NAME, "Title", "MapleStory", g_pConfig->szWndTitle, 255, OPT_CFG_FILE);
	Log("\t Title: %s", g_pConfig->szWndTitle);

	g_pConfig->nPortLow = GetPrivateProfileIntA(OPT_CFG_NAME, "PortLow", 8484, OPT_CFG_FILE);
	Log("\t PortLow: %d", g_pConfig->nPortLow);

	g_pConfig->nPortHigh = GetPrivateProfileIntA(OPT_CFG_NAME, "PortHigh", 8989, OPT_CFG_FILE);
	Log("\t PortHigh: %d", g_pConfig->nPortHigh);
}

DWORD WINAPI MainProc(PVOID)
{
	g_dwPID = GetCurrentProcessId();

	HeaderProc();
	ConfigProc();

	if (!HookSockApi())
		Log("Failed Hooking SockApi");

	if (!HookWinApi())
		Log("Failed Hooking WinApi");

	if (!HookMapleApi())
		Log("Failed Hooking MapleApi");

	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hinstDLL);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&MainProc, NULL, NULL, NULL);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		Log("[%s] [v%s] [PID: %d] Detaching", OPT_APP_NAME, OPT_APP_VERSION, g_dwPID);
	}

	return TRUE;
}