#ifndef DLL_INJECTOR_C_INJECT_H
#define DLL_INJECTOR_C_INJECT_H

#include <stdbool.h>

#include <Windows.h>

bool InjectDll(const DWORD processId, const char* dllLocation);

#endif // DLL_INJECTOR_C_INJECT_H