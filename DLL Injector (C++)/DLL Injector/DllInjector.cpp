#include "DllInjector.h"
#include <stdexcept>

DllInjector::DllInjector(Process& process)
	:
	process{ process }
{
}

void DllInjector::InjectDll(const char* dllLocation) const
{
	HMODULE kernel32Handle = GetModuleHandle("kernel32.dll");

	if (kernel32Handle == nullptr)
	{
		throw std::runtime_error{ "Could not load Kernel32.dll." };
	}

	FARPROC loadLibrary = GetProcAddress(kernel32Handle, "LoadLibraryA");

	if (loadLibrary == nullptr)
	{
		throw std::runtime_error{ "Could not load the LoadLibraryA module of Kernel32.dll." };
	}

	HANDLE processHandle = process.Open();

	LPVOID dllLocationAllocationAddress = VirtualAllocEx(processHandle, nullptr, strlen(dllLocation), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

	if (dllLocationAllocationAddress == nullptr)
	{
		throw std::runtime_error{ "Could not allocate memory in target process." };
	}

	const BOOL memoryWriteSucceeded = WriteProcessMemory(processHandle, dllLocationAllocationAddress, dllLocation, strlen(dllLocation), nullptr);

	if (memoryWriteSucceeded == 0)
	{
		throw std::runtime_error{ "Could not write DLL location to process memory." };
	}

	HANDLE dllThreadHandle = CreateRemoteThread(processHandle, nullptr, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(loadLibrary), dllLocationAllocationAddress, 0, nullptr);

	if (dllThreadHandle == nullptr)
	{
		throw std::runtime_error{ "Could not launch DLL thread in target process." };
	}

	CloseHandle(dllThreadHandle);
}