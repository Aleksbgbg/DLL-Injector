namespace Dll.Injector.Services
{
    using Dll.Injector.Services.Interfaces;

    using Microsoft.Win32;

    internal class FileBrowserService : IFileBrowserService
    {
        public string OpenFile(string title, string filter)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog
            {
                CheckFileExists = true,
                Filter = filter,
                InitialDirectory = System.AppDomain.CurrentDomain.BaseDirectory,
                Title = title
            };

            // Returns bool? so value could be 'null'
            if (openFileDialog.ShowDialog() == true)
            {
                return openFileDialog.FileName;
            }

            return null;
        }
    }
}