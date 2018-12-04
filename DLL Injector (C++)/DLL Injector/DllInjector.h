#pragma once

#include "Process.h"

class DllInjector
{
public:
	explicit DllInjector(Process& process);

public:
	void InjectDll(const char* dllLocation) const;

private:
	Process& process;
};