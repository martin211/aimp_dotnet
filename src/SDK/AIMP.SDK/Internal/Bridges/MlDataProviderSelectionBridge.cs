using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpDataProviderSelection"/> to the native
    /// <c>IAIMPMLDataProviderSelection</c> vtable.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class MlDataProviderSelectionBridge : IAIMPMLDataProviderSelectionNative
    {
        private readonly IAimpDataProviderSelection _selection;
        private IntPtr _stringValue = IntPtr.Zero;

        public MlDataProviderSelectionBridge(IAimpDataProviderSelection selection)
        {
            _selection = selection ?? throw new ArgumentNullException(nameof(selection));
        }

        [PreserveSig]
        public double GetValueAsFloat(int fieldIndex)
        {
            return Safe.Run(() => _selection.GetValueAsFloat(fieldIndex), 0d);
        }

        [PreserveSig]
        public int GetValueAsInt32(int fieldIndex)
        {
            return Safe.Run(() => _selection.GetValueAsInt32(fieldIndex), 0);
        }

        [PreserveSig]
        public long GetValueAsInt64(int fieldIndex)
        {
            return Safe.Run(() => _selection.GetValueAsInt64(fieldIndex), 0L);
        }

        [PreserveSig]
        public IntPtr GetValueAsString(int fieldIndex, out int length)
        {
            FreeString();

            var text = Safe.Run(() => _selection.GetValueAsString(fieldIndex), null);

            if (text == null)
            {
                length = 0;
                return IntPtr.Zero;
            }

            _stringValue = AimpString.CreateNative(text);
            length = text.Length;
            return _stringValue;
        }

        [PreserveSig]
        public int NextRow()
        {
            try
            {
                return _selection.NextRow() ? 1 : 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }

        private void FreeString()
        {
            if (_stringValue != IntPtr.Zero)
            {
                AimpComHelper.Release(_stringValue);
                _stringValue = IntPtr.Zero;
            }
        }
    }
}