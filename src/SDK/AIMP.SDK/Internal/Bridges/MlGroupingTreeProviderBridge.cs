using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.Internal.Runtime.MusicLibrary;
using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpGroupingTreeDataProvider"/> to the native
    /// <c>IAIMPMLGroupingTreeDataProvider2</c> vtable.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class MlGroupingTreeProviderBridge : IAIMPMLGroupingTreeDataProvider2Native
    {
        private readonly IAimpGroupingTreeDataProvider _provider;

        public MlGroupingTreeProviderBridge(IAimpGroupingTreeDataProvider provider)
        {
            _provider = provider ?? throw new ArgumentNullException(nameof(provider));
        }

        [PreserveSig]
        public int AppendFilter(IntPtr filter, IntPtr selection)
        {
            return Safe.Run(() =>
            {
                using (var group = new AimpDataFilterGroupWrapper(AimpComHelper.AddRef(filter)))
                using (var treeSelection = new AimpGroupingTreeSelectionWrapper(selection))
                {
                    return ToHResult(_provider.AppendFilter(group, treeSelection));
                }
            });
        }

        [PreserveSig]
        public uint GetCapabilities()
        {
            return Safe.Run(() => (uint)_provider.GetCapabilities(), 0u);
        }

        [PreserveSig]
        public int GetData(IntPtr selection, out IntPtr data)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                using (var treeSelection = new AimpGroupingTreeSelectionWrapper(selection))
                {
                    var nodeSelection = _provider.GetData(treeSelection);
                    if (nodeSelection.ResultType != ActionResultType.OK || nodeSelection.Result == null)
                    {
                        return (int)nodeSelection.ResultType;
                    }

                    result = AimpComHelper.GetPointer(
                        new MlGroupingTreeSelectionBridge(nodeSelection.Result),
                        typeof(IAIMPMLGroupingTreeDataProviderSelectionNative));

                    return Safe.S_OK;
                }
            });

            data = result;
            return hr;
        }

        [PreserveSig]
        public int GetFieldForAlphabeticIndex(out IntPtr fieldName)
        {
            var result = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var value = _provider.GetFieldForAlphabeticIndex();
                if (value.ResultType != ActionResultType.OK)
                {
                    return (int)value.ResultType;
                }

                result = AimpString.CreateNative(value.Result ?? string.Empty);
                return Safe.S_OK;
            });

            fieldName = result;
            return hr;
        }

        [PreserveSig]
        public ushort GetPathSeparator()
        {
            return (ushort)'\\';
        }

        private static int ToHResult(AimpActionResult result)
        {
            return result == null ? Safe.E_FAIL : (int)result.ResultType;
        }
    }
}