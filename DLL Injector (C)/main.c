#include <stdio.h>

#include "FindProcess.h"

#define USAGE "DllInject.exe <DLL_LOCATION> [-c <PROCESS_LOCATION> | -n <PROCESS_NAME> | -w <PROCESS_WINDOW_TITLE>]"

void WriteInvalidUsage(const char* message)
{
    printf("Invalid usage. %s.\nUsage: %s", message, USAGE);
}

int main(const int argumentCount, char** argumentValues)
{
    if (argumentCount != 4)
    {
        WriteInvalidUsage("Invalid argument count");
        return EXIT_FAILURE;
    }

    if (GetFileAttributes(argumentValues[1]) == INVALID_FILE_ATTRIBUTES)
    {
        printf("DLL file does not exist.");
        return EXIT_FAILURE;
    }

    DWORD processId;
    HANDLE mainThreadHandle = NULL;

    const char* targetSwitch = argumentValues[2];

    if (strlen(targetSwitch) != 2 || targetSwitch[0] != '-')
    {
        WriteInvalidUsage("Invalid process identifier switch");
        return EXIT_FAILURE;
    }

    const char processIdentifierSwitch = (char)tolower(argumentValues[2][1]);
    char* processIdentifier = argumentValues[3];

    switch (processIdentifierSwitch)
    {
        case 'c':
            processId = FindProcessByCreation(processIdentifier, &mainThreadHandle);
            break;

        case 'n':
            processId = FindProcessByName(processIdentifier);
            break;

        case 'w':
            processId = FindProcessByWindowTitle(processIdentifier);
            break;

        default:
            WriteInvalidUsage("Invalid identifier switch");
            return EXIT_FAILURE;
    }

    if (processId == 0)
    {
        printf("Could not find process.");
        return EXIT_FAILURE;
    }

    printf("Process found. ID: %i", processId);

    // Inject here

    if (processIdentifierSwitch == 'c')
    {
        ResumeThread(mainThreadHandle);
        CloseHandle(mainThreadHandle);
    }

    return EXIT_SUCCESS;
}