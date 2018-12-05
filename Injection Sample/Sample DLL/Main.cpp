#include <iostream>

#include <Windows.h>

BOOL APIENTRY DllMain(HANDLE moduleHandle, const DWORD callReason, LPVOID lpReserved)
{
    switch (callReason)
    {
    case DLL_PROCESS_ATTACH:
		std::cout << "DLL attached!\n";
		break;

    case DLL_THREAD_ATTACH:
    	break;

    case DLL_THREAD_DETACH:
    	break;

    case DLL_PROCESS_DETACH:
		std::cout << "DLL detached!\n";
    	break;
    }

    return TRUE;
}