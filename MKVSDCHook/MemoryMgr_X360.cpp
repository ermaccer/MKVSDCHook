#include "MemoryMgr_X360.h"


void Nop(uintptr_t addr)
{
	Patch<int>(addr, 0);
}

void Blr(uintptr_t addr)
{
	Patch<int>(addr, 0x4E800020);
}