namespace Dll.Injector.Services
{
    using System.Runtime.InteropServices;

    using Dll.Injector.Services.Interfaces;

    internal class DllInjectionService : IDllInjectionService
    {
        public bool Inject(uint processId, string dllLocation)
        {
            return InjectDll(processId, dllLocation);
        }

        [DllImport("Inject.dll")]
        private static extern bool InjectDll(uint processId, string dllLocation);
    }
}