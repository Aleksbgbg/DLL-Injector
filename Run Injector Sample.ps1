param(
	[string] $injectorPath = "Release\DLL Injector (C).exe",
	[string] $consoleAppPath = "Release\Sample Console.exe",
	[string] $dllPath = "Release\Sample DLL.dll"
)

Start-Process $consoleAppPath

$consoleAppName = Split-Path $consoleAppPath -Leaf

& $injectorPath $dllPath -n $consoleAppName