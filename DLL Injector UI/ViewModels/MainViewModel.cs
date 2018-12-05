namespace Dll.Injector.ViewModels
{
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Windows.Data;

    using Caliburn.Micro;

    using Dll.Injector.Services.Interfaces;
    using Dll.Injector.ViewModels.Interfaces;

    internal class MainViewModel : ViewModelBase, IMainViewModel
    {
        private readonly IDllInjectionService _dllInjectionService;

        private readonly IFileBrowserService _fileBrowserService;

        public MainViewModel(IDllInjectionService dllInjectionService, IFileBrowserService fileBrowserService, IProcessService processService)
        {
            _dllInjectionService = dllInjectionService;
            _fileBrowserService = fileBrowserService;

            Processes = new BindableCollection<Process>(processService.ListProcesses());

            CollectionViewSource.GetDefaultView(Processes).SortDescriptions.Add(new SortDescription(nameof(Process.StartTime), ListSortDirection.Descending));
        }

        public IObservableCollection<Process> Processes { get; }

        private Process _selectedProcess;
        public Process SelectedProcess
        {
            get => _selectedProcess;

            set
            {
                if (_selectedProcess == value) return;

                _selectedProcess = value;
                NotifyOfPropertyChange(() => SelectedProcess);
                NotifyOfPropertyChange(() => CanInject);
            }
        }

        private string _dllPath = string.Empty;
        public string DllPath
        {
            get => _dllPath;

            private set
            {
                if (_dllPath == value) return;

                _dllPath = value;
                NotifyOfPropertyChange(() => DllPath);
                NotifyOfPropertyChange(() => CanInject);
            }
        }

        public bool CanInject => SelectedProcess != null && !string.IsNullOrEmpty(DllPath);

        public void OpenDll()
        {
            string dllPath = _fileBrowserService.OpenFile("Select DLL to inject", "Dynamic Link Library (DLL)|*.dll");

            if (dllPath != null)
            {
                DllPath = dllPath;
            }
        }

        public void Inject()
        {
            _dllInjectionService.Inject((uint)SelectedProcess.Id, DllPath);
        }
    }
}