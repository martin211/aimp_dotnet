using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpGroupingTreeDataProviderSelection"/> to the
    /// native selection vtable.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class MlGroupingTreeSelectionBridge : IAIMPMLGroupingTreeDataProviderSelectionNative
    {
        private readonly IAimpGroupingTreeDataProviderSelection _selection;

        public MlGroupingTreeSelectionBridge(IAimpGroupingTreeDataProviderSelection selection)
        {
            _selection = selection ?? throw new ArgumentNullException(nameof(selection));
        }

        [PreserveSig]
        public int GetDisplayValue(out IntPtr value)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var display = _selection.GetDisplayValue();
                if (display.ResultType != ActionResultType.OK)
                {
                    return (int)display.ResultType;
                }

                result = AimpString.CreateNative(display.Result ?? string.Empty);
                return Safe.S_OK;
            });

            value = result;
            return hr;
        }

        [PreserveSig]
        public uint GetFlags()
        {
            return Safe.Run(() => (uint)_selection.GetFlags(), 0u);
        }

        [PreserveSig]
        public int GetImageIndex(out int index)
        {
            var value = 0;

            var hr = Safe.Run(() =>
            {
                var image = _selection.GetImageIndex();
                if (image.ResultType == ActionResultType.OK)
                {
                    value = (int)image.Result;
                }

                return (int)image.ResultType;
            });

            index = value;
            return hr;
        }

        [PreserveSig]
        public int GetValue(out IntPtr fieldName, IntPtr value)
        {
            var name = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var pair = _selection.GetValue();
                if (pair.ResultType != ActionResultType.OK)
                {
                    return (int)pair.ResultType;
                }

                name = AimpString.CreateNative(pair.Item1 ?? string.Empty);

                if (value != IntPtr.Zero)
                {
                    Marshal.GetNativeVariantForObject(pair.Item2, value);
                }

                return Safe.S_OK;
            });

            fieldName = name;
            return hr;
        }

        [PreserveSig]
        public int NextRecord()
        {
            try
            {
                return _selection is IAimpGroupingTreeDataProviderSelection2 selection2
                    ? (selection2.NextRow() ? 1 : 0)
                    : (_selection.NextRecord() ? 1 : 0);
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }
    }
}