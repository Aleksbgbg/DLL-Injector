#include <iostream>

#include "Process.hpp"
#include "DllInjector.hpp"

#define USAGE "DllInject.exe <DLL_LOCATION> [-c <PROCESS_LOCATION> | -n <PROCESS_NAME> | -w <PROCESS_WINDOW_TITLE>]"

void WriteInvalidUsage(const char* message)
{
	std::cout << "Invalid usage." << message << ".\nUsage: " << USAGE << "\n";
}

int main(const int argumentCount, char** argumentValues)
{
	if (argumentCount != 4)
	{
		WriteInvalidUsage("Invalid argument count");
		return -1;
	}

	const char* dllLocation = argumentValues[1];

	if (GetFileAttributes(dllLocation) == INVALID_FILE_ATTRIBUTES)
	{
		std::cout << "DLL file does not exist.\n";
		return -1;
	}

	const char* targetSwitch = argumentValues[2];

	if (strlen(targetSwitch) != 2 || targetSwitch[0] != '-')
	{
		WriteInvalidUsage("Invalid process identifier switch");
		return -1;
	}

	const char processIdentifierSwitch = static_cast<char>(tolower(argumentValues[2][1]));
	char* processIdentifier = argumentValues[3];

	Process process;

	try
	{
		switch (processIdentifierSwitch)
		{
		case 'c':
			process = Process::Create(processIdentifier);
			break;

		case 'n':
			process = Process::FindByName(processIdentifier);
			break;

		case 'w':
			process = Process::FindByWindowTitle(processIdentifier);
			break;

		default:
			WriteInvalidUsage("Invalid identifier switch");
			return -1;
		}
	}
	catch (std::runtime_error&)
	{
		std::cout << "Could not find process.\n";
		return -1;
	}

	std::cout << "Process found.\nInjecting...\n";

	{
		DllInjector injector{ process };

		try
		{
			injector.InjectDll(dllLocation);
			std::cout << "Injection successful.\n";
		}
		catch (std::runtime_error&)
		{
			std::cout << "Injection unsuccessful.\n";
		}
	}

	if (processIdentifierSwitch == 'c')
	{
		process.ResumeMainThread();
	}

	return 0;
}