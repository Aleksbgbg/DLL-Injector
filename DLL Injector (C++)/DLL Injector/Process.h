#pragma once

#include "Windows.h"

class Process
{
public:
	Process();
	Process(const Process&) = delete;
	Process(Process&& source) noexcept;

public:
	~Process();

public:
	Process& operator=(const Process&) = delete;
	Process& operator=(Process&& source) noexcept;

public:
	void ResumeMainThread() const;

	HANDLE Open();

public:
	static Process Create(char* location);
	static Process FindByName(const char* name);
	static Process FindByWindowTitle(const char* windowTitle);

private:
	explicit Process(const DWORD id);
	Process(const DWORD id, HANDLE mainThread);

private:
	DWORD id;
	HANDLE handle;
	HANDLE mainThread;
};