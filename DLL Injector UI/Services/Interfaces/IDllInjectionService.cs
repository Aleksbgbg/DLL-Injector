namespace Dll.Injector.Services.Interfaces
{
    internal interface IDllInjectionService
    {
        bool Inject(uint processId, string dllLocation);
    }
}