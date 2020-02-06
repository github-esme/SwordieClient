#include <Windows.h>
#include "Config.h"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "detours.lib")

#define ZXString char*

//---------------------------------------------------------------------------------------------

#define OPT_APP_NAME		"SwordieClient"
#define OPT_APP_VERSION		"1.1"
#define OPT_CFG_FILE		".\\Swordie.ini"
#define OPT_CFG_NAME		"Client"

//---------------------------------------------------------------------------------------------

extern Config* g_pConfig;

//---------------------------------------------------------------------------------------------

void FuckMaple();

bool HookWinApi();
bool HookSockApi();
bool HookMapleApi();

//---------------------------------------------------------------------------------------------

void Log(const char* format, ...);

void PatchJmp(DWORD dwAddress, DWORD dwDest);
void PatchRetZero(DWORD dwAddress);
void PatchNop(DWORD dwAddress, DWORD dwCount);

DWORD GetFuncAddress(LPCSTR lpModule, LPCSTR lpFunc);

BOOL SetHook(BOOL bInstall, PVOID* ppvTarget, PVOID pvDetour);

//---------------------------------------------------------------------------------------------