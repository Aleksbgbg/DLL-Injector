#ifndef DLL_INJECTOR_C_FINDPROCESS_H
#define DLL_INJECTOR_C_FINDPROCESS_H

#include "Windows.h"

DWORD FindProcessByCreation(char* location, HANDLE* mainThreadHandle);

DWORD FindProcessByName(const char* name);

#endif //DLL_INJECTOR_C_FINDPROCESS_H