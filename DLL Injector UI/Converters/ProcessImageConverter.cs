namespace Dll.Injector.Converters
{
    using System;
    using System.ComponentModel;
    using System.Diagnostics;
    using System.Drawing;
    using System.Globalization;
    using System.Runtime.InteropServices;
    using System.Windows;
    using System.Windows.Data;
    using System.Windows.Interop;
    using System.Windows.Media.Imaging;

    [ValueConversion(typeof(Process), typeof(BitmapSource))]
    internal class ProcessImageConverter : IValueConverter
    {
        private const int ImageRetrievalFlag = 0x100; // Flag 0x100 represents 'SHGFI_ICON' (retrieves the handle to the file icon)

        public static ProcessImageConverter Default { get; } = new ProcessImageConverter();

        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            Process process = (Process)value;

            if (process == null)
            {
                throw new ArgumentNullException(nameof(value));
            }

            string processFilepath;

            try
            {
                processFilepath = process.MainModule.FileName;
            }
            catch (InvalidOperationException)
            {
                return null;
            }
            catch (Win32Exception)
            {
                return null;
            }

            if (string.IsNullOrEmpty(processFilepath))
            {
                return null;
            }

            ShFileInfo shFileInfo = new ShFileInfo();

            SHGetFileInfo(processFilepath, 0u, ref shFileInfo, (uint)Marshal.SizeOf(shFileInfo), ImageRetrievalFlag);

            return Imaging.CreateBitmapSourceFromHBitmap(Icon.FromHandle(shFileInfo.iconHandle)
                                                             .ToBitmap()
                                                             .GetHbitmap(),
                                                         IntPtr.Zero,
                                                         Int32Rect.Empty,
                                                         BitmapSizeOptions.FromEmptyOptions());
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            throw new NotSupportedException("ConvertBack is not supported");
        }

        [DllImport("Shell32.dll")]
        private static extern IntPtr SHGetFileInfo(string filePath, uint fileAttributes, ref ShFileInfo shFileInfoPointer, uint imagePointerSize, uint flags);

        [StructLayout(LayoutKind.Sequential)]
        private struct ShFileInfo
        {
            public readonly IntPtr iconHandle;

            public readonly int iconIndex;

            public readonly uint fileAttributes;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 260)]
            public readonly string fileName;

            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 80)]
            public readonly string fileType;
        }
    }
}