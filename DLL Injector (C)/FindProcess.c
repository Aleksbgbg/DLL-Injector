#include "FindProcess.h"

#include <stdbool.h>

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