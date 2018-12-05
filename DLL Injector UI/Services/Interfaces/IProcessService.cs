namespace Dll.Injector.Services.Interfaces
{
    using System.Diagnostics;

    internal interface IProcessService
    {
        Process[] ListProcesses();
    }
}