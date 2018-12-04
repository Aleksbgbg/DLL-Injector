#include "Process.h"
#include <stdexcept>

Process::Process(const DWORD id)
	:
	id{ id },
	mainThread{ nullptr }
{
}

Process::Process(const DWORD id, HANDLE mainThread)
	:
	id{ id },
	mainThread{ mainThread }
{
}

Process::Process(Process&& source) noexcept
	:
	id{ source.id },
	mainThread{ source.mainThread }
{
	source.id = 0;
	source.mainThread = nullptr;
}

Process& Process::operator=(Process&& source) noexcept
{
	id = source.id;
	mainThread = source.mainThread;

	source.id = 0;
	source.mainThread = nullptr;

	return *this;
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

Process::~Process()
{
	if (mainThread != nullptr)
	{
		CloseHandle(mainThread);
	}
}