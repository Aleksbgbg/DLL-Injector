#include "Process.h"

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

Process::~Process()
{
	if (mainThread != nullptr)
	{
		CloseHandle(mainThread);
	}
}
