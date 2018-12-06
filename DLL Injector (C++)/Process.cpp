#include "Process.hpp"

#include <cassert>
#include <stdexcept>

#include "TlHelp32.h"

Process::Process(const DWORD id)
	:
	id{ id },
	handle{ nullptr },
	mainThread{ nullptr }
{
}

Process::Process(const DWORD id, HANDLE mainThread)
	:
	id{ id },
	handle{ nullptr },
	mainThread{ mainThread }
{
}

Process::Process()
	:
	id{ 0 },
	handle{ nullptr },
	mainThread{ nullptr }
{
}

Process::Process(Process&& source) noexcept
	:
	id{ source.id },
	handle{ source.handle },
	mainThread{ source.mainThread }
{
	source.id = 0;
	source.handle = nullptr;
	source.mainThread = nullptr;
}

Process::~Process()
{
	if (handle != nullptr)
	{
		CloseHandle(handle);
	}

	if (mainThread != nullptr)
	{
		CloseHandle(mainThread);
	}
}

Process& Process::operator=(Process&& source) noexcept
{
	assert(this != &source);

	id = source.id;
	handle = source.handle;
	mainThread = source.mainThread;

	source.id = 0;
	source.handle = nullptr;
	source.mainThread = nullptr;

	return *this;
}

void Process::ResumeMainThread() const
{
	if (mainThread == nullptr)
	{
		throw std::runtime_error{ "Main thread does not exist." };
	}

	ResumeThread(mainThread);
}

void Process::WithId(const id_consumer consumer) const
{
	consumer(id);
}

HANDLE Process::Open()
{
	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, false, id);

	if (handle == nullptr)
	{
		throw std::runtime_error{ "Could not open process." };
	}

	this->handle = handle;

	return handle;
}

Process Process::Create(char* location)
{
	STARTUPINFO startupInfo = { };
	startupInfo.cb = sizeof(STARTUPINFO);

	PROCESS_INFORMATION processInformation = { };

	// Passing the process location as a command-line argument instead of an application name
	// will allow the user to insert custom command line parameters when creating the process
	if (CreateProcess(nullptr, location, nullptr, nullptr, false, CREATE_SUSPENDED, nullptr, nullptr, &startupInfo, &processInformation))
	{
		HANDLE mainThreadHandle = reinterpret_cast<HANDLE>(processInformation.hThread);

		return Process{ processInformation.dwProcessId, mainThreadHandle };
	}

	throw std::runtime_error{ "Cannot create process at specified location." };
}

Process Process::FindByName(const char* name)
{
	HANDLE snapshotHandle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	PROCESSENTRY32 processEntry = { };
	processEntry.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(snapshotHandle, &processEntry))
	{
		do
		{
			if (strcmp(processEntry.szExeFile, name) == 0)
			{
				CloseHandle(snapshotHandle);
				return Process{ processEntry.th32ProcessID };
			}
		} while (Process32Next(snapshotHandle, &processEntry));
	}

	CloseHandle(snapshotHandle);

	throw std::runtime_error{ "Process not found." };
}

Process Process::FindByWindowTitle(const char* windowTitle)
{
	HWND windowHandle = FindWindow(nullptr, windowTitle);

	if (windowHandle == nullptr)
	{
		throw std::runtime_error{ "Could not find window." };
	}

	DWORD processId;

	GetWindowThreadProcessId(windowHandle, &processId);

	return Process{ processId };
}