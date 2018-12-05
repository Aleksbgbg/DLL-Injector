param(
	[string] $injectorPath = "DLL Injector (C)\cmake-build-release\DLL_Injector__C_.exe",
	[string] $consoleAppPath = "Injection Sample\Release\Sample Console.exe",
	[string] $dllPath = "Injection Sample\Release\Sample DLL.dll"
)

Start-Process $consoleAppPath

$consoleAppName = Split-Path $consoleAppPath -Leaf

& $injectorPath $dllPath -n $consoleAppName