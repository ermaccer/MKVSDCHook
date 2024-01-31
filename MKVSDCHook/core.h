#pragma once
#include <xtl.h>
#include <cstdint>


void *ResolveFunction(const char* name, unsigned int ordinal);

typedef void (*XNOTIFYQUEUEUI)(uint32_t type, uint32_t userIndex, uint64_t areas, const wchar_t *displayText, void *pContextData);
extern XNOTIFYQUEUEUI XNotifyQueueUI;