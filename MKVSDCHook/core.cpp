#include "core.h"

// Get the address of a function from a module by its ordinal
void *ResolveFunction(const char* name, unsigned int ordinal)
{
    HMODULE moduleHandle = GetModuleHandle(name);
    if (moduleHandle == nullptr)
        return nullptr;

    return GetProcAddress(moduleHandle, reinterpret_cast<const char *>(ordinal));
}

XNOTIFYQUEUEUI XNotifyQueueUI = static_cast<XNOTIFYQUEUEUI>(ResolveFunction("xam.xex", 656));