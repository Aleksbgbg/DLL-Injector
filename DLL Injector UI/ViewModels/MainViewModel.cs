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
        public MainViewModel(IProcessService processService)
        {
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
            }
        }
    }
}