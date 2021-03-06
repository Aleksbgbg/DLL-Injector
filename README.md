# DLL Injector
Simple DLL injector.

Both C (procedural) and C++ (OOP) variants have been included, although they both function quite similarly.

A C# WPF interface has also been created.

Can be used to patch functions of the target process to execute custom code.

## User Interface Example
### Process List
![Process List](/Preview/Process%20List.png)

### Injection Example
![Injection Example](/Preview/Injection%20Example.png)

## How does it work?
Quite simply.

First, the injector allocates the location of the target DLL into the target process' virtual address space. Next, the injector will create a remote thread (hosted in the target process) and dynamically invoke `LoadLibraryA` from this thread, passing the DLL location parameter as the address of the earlier allocation, causing the target DLL to be loaded into the target process' address space.