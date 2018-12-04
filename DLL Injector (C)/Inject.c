#include "Inject.h"

bool InjectDll(const DWORD processId, const char* dllLocation)
{
    HMODULE kernel32Handle = GetModuleHandle("kernel32.dll");

    if (kernel32Handle == NULL)
    {
        return false;
    }

    FARPROC loadLibrary = GetProcAddress(kernel32Handle, "LoadLibraryA");

    if (loadLibrary == NULL)
    {
        return false;
    }

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processId);

    if (processHandle == NULL)
    {
        return false;
    }

    LPVOID dllAddress = VirtualAllocEx(processHandle, NULL, strlen(dllLocation), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    if (dllAddress == NULL)
    {
        CloseHandle(processHandle);
        return false;
    }

    const BOOL memoryWriteSucceeded = WriteProcessMemory(processHandle, dllAddress, dllLocation, strlen(dllLocation), NULL);

    if (memoryWriteSucceeded == 0)
    {
        CloseHandle(processHandle);
        return false;
    }

    HANDLE dllThreadHandle = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)loadLibrary, dllAddress, 0, NULL);

    CloseHandle(processHandle);

    if (dllThreadHandle == NULL)
    {
        return false;
    }

    CloseHandle(dllThreadHandle);

    return true;
}