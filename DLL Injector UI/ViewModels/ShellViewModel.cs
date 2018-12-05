namespace Dll.Injector.ViewModels
{
    using Dll.Injector.ViewModels.Interfaces;

    internal sealed class ShellViewModel : ViewModelBase, IShellViewModel
    {
        public ShellViewModel(IMainViewModel mainViewModel)
        {
            DisplayName = "DLL Injector";

            MainViewModel = mainViewModel;
        }

        public IMainViewModel MainViewModel { get; }
    }
}