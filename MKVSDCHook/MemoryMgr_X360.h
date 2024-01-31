#pragma once
#include <xtl.h>

template<typename T>
void Patch(uintptr_t addr, T data)
{
	DWORD		dwProtect;
	VirtualProtect((void*)addr, sizeof(data), PAGE_EXECUTE_READWRITE, &dwProtect);
	*(T*)(addr) = data;
	VirtualProtect((void*)addr, sizeof(data), dwProtect, &dwProtect);
}

void Nop(uintptr_t addr);
void Blr(uintptr_t addr);