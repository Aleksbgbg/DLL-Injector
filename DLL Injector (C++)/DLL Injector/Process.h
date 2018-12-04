#pragma once

#include "Windows.h"

class Process
{
public:
	Process(const Process&) = delete;
	Process(Process&& source) noexcept;

public:
	~Process();

public:
	Process& operator=(const Process&) = delete;
	Process& operator=(Process&& source) noexcept;

public:
	static Process Create(char* location);

private:
	explicit Process(const DWORD id);
	Process(const DWORD id, HANDLE mainThread);

private:
	DWORD id;
	HANDLE mainThread;
};