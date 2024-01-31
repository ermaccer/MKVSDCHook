#include "core.h"
#include <cstdint>
#include <xtl.h>
#include "mk8.h"
#include "MemoryMgr_X360.h"

// Imports from the Xbox libraries
extern "C"
{
    uint32_t XamGetCurrentTitleId();

    uint32_t ExCreateThread(
        HANDLE *pHandle,
        uint32_t stackSize,
        uint32_t *pThreadId,
        void *pApiThreadStartup,
        PTHREAD_START_ROUTINE pStartAddress,
        void *pParameter,
        uint32_t creationFlags
    );
}

void Init()
{
	Sleep(500);
	CreateThread(nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(MK8_UpdateThread), nullptr, 0, 0);
}


bool g_Running = true;

// based off https://github.com/ClementDreptin/ModdingResources

// Infinitely check the current game running
uint32_t MonitorTitleId(void *pThreadParameter)
{
    uint32_t currentTitleId = 0;

    while (g_Running)
    {
        uint32_t newTitleId = XamGetCurrentTitleId();

        if (newTitleId == currentTitleId)
            continue;

        currentTitleId = newTitleId;

		if (newTitleId == 0x4D5707E9)
		{
			XNotifyQueueUI(0, 0, XNOTIFY_SYSTEM, L"MKVSDCHook installed correctly!", nullptr);
			Init();
		}
    }

    return 0;
}

int DllMain(HANDLE hModule, DWORD reason, void *pReserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
        // Run MonitorTitleId in separate thread
        ExCreateThread(nullptr, 0, nullptr, nullptr, reinterpret_cast<LPTHREAD_START_ROUTINE>(MonitorTitleId), nullptr, 2);
        break;
    case DLL_PROCESS_DETACH:
        g_Running = false;
        // We give the system some time to clean up the thread before exiting
        Sleep(250);
        break;
    }

    return TRUE;
}