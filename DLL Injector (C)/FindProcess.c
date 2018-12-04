#include "FindProcess.h"

#include <stdbool.h>

#include "TlHelp32.h"

DWORD FindProcessByCreation(char* location, HANDLE* mainThreadHandle)
{
    STARTUPINFO startupInfo = { };
    startupInfo.cb = sizeof(STARTUPINFO);

    PROCESS_INFORMATION processInformation = { };

    // Passing the process location as a command-line argument instead of an application name
    // will allow the user to insert custom command line parameters when creating the process
    if (CreateProcess(NULL, location, NULL, NULL, false, CREATE_SUSPENDED, NULL, NULL, &startupInfo, &processInformation))
    {
        *mainThreadHandle = (HANDLE)processInformation.hThread;
        return processInformation.dwProcessId;
    }

    return 0;
}

DWORD FindProcessByName(const char* name)
{
    HANDLE systemProcessesSnapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    PROCESSENTRY32 processEntry = { };
    processEntry.dwSize = sizeof(PROCESSENTRY32);

    DWORD processId = 0;

    if (Process32First(systemProcessesSnapshotHandle, &processEntry))
    {
        do
        {
            if (strcmp(processEntry.szExeFile, name) == 0)
            {
                processId = processEntry.th32ProcessID;
                break;
            }
        } while (Process32Next(systemProcessesSnapshotHandle, &processEntry));
    }

    CloseHandle(systemProcessesSnapshotHandle);

    return processId;
}