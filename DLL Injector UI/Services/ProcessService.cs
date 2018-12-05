namespace Dll.Injector.Services
{
    using System.Diagnostics;

    using Dll.Injector.Services.Interfaces;

    internal class ProcessService : IProcessService
    {
        public Process[] ListProcesses()
        {
            return Process.GetProcesses();
        }
    }
}