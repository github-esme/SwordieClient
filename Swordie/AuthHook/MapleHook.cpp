#include "Global.h"
#include <intrin.h>

void FuckMaple()
{
	Log(__FUNCTION__);

	PatchRetZero(0x01960B00);//NGS Removal
	PatchJmp(0x019DD7AD, 0x019DD844);//MSCRC Bypass
}

bool Hook_WriteStageLogA(bool bEnable)
{
	typedef int(__cdecl* pWriteStageLogA)(int nIdx, ZXString szMessage);
	static auto _WriteStageLogA = (pWriteStageLogA)(GetFuncAddress("nxgsm", "WriteStageLogA"));

	pWriteStageLogA Hook = [](int nIdx, ZXString szMessage) -> int
	{
		Log("WriteStageLogA: %s", szMessage);
		return 0;
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_WriteStageLogA), Hook);
}

bool Hook_WriteErrorLogA(bool bEnable)
{
	typedef int(__cdecl* pWriteErrorLogA)(int nIdx, ZXString szMessage);
	static auto _WriteErrorLogA = (pWriteErrorLogA)(GetFuncAddress("nxgsm", "WriteErrorLogA"));

	pWriteErrorLogA Hook = [](int nIdx, ZXString szMessage) -> int
	{
		Log("WriteErrorLogA: %s", szMessage);
		return 0;
	};

	return SetHook(bEnable, reinterpret_cast<void**>(&_WriteErrorLogA), Hook);
}

bool HookMapleApi()
{
	bool bResult = true;

	bResult &= Hook_WriteStageLogA(true);
	bResult &= Hook_WriteErrorLogA(true);

	return bResult;
}