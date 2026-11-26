using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.Internal.Bridges;

/// <summary>
/// CCW adapter for <see cref="IAimpExtensionExternalCatalog"/>.
/// </summary>
[ComVisible(true)]
[ClassInterface(ClassInterfaceType.None)]
internal sealed class ExternalCatalogBridge : IAIMPExtensionExternalCatalogNative
{
    private readonly IAimpExtensionExternalCatalog _catalog;

    public ExternalCatalogBridge(IAimpExtensionExternalCatalog catalog)
    {
        _catalog = catalog ?? throw new ArgumentNullException(nameof(catalog));
    }

    public int GetIcon(out IntPtr image)
    {
        var resultImage = IntPtr.Zero;
        var hr = Safe.Run(() =>
        {
            var result = _catalog.GetIcon();
            if (result.ResultType == ActionResultType.OK && result.Result is IAimpNativeObject native)
            {
                resultImage = native.NativePointer;
            }

            return (int)result.ResultType;
        });

        image = resultImage;
        return hr;
    }

    public int GetName(out IntPtr name)
    {
        var resultName = IntPtr.Zero;
        var hr = Safe.Run(() =>
        {
            var result = _catalog.GetName();
            if (result.ResultType == ActionResultType.OK)
            {
                resultName = AimpString.CreateNative(result.Result ?? string.Empty);
            }

            return (int)result.ResultType;
        });

        name = resultName;
        return hr;
    }

    public int Show(IntPtr ownerWindow, IntPtr data)
    {
        return Safe.Run(() =>
        {
            object managedData = null;

            if (data != IntPtr.Zero)
            {
                managedData = Marshal.GetObjectForIUnknown(data);
            }

            try
            {
                return (int)_catalog.Show(ownerWindow, managedData).ResultType;
            }
            finally
            {
                if (managedData != null)
                {
                    Marshal.ReleaseComObject(managedData);
                }
            }
        });
    }
}