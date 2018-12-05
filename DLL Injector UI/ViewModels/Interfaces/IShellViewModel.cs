namespace Dll.Injector.ViewModels.Interfaces
{
    internal interface IShellViewModel : IViewModelBase
    {
        IMainViewModel MainViewModel { get; }
    }
}