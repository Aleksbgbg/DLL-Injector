#ifndef DLL_INJECTOR_C_INJECT_H
#define DLL_INJECTOR_C_INJECT_H

#include <stdbool.h>

#include <Windows.h>

__declspec(dllexport)
bool __stdcall InjectDll(const DWORD processId, const char* dllLocation);

#endif // DLL_INJECTOR_C_INJECT_H