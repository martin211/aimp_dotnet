using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MusicLibrary;
using AIMP.SDK.MusicLibrary;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// CCW adapter for one grouping preset sort field.
    ///
    /// AIMP expects every item in <c>IAIMPMLGroupingPresets::Add2</c> to
    /// implement both <c>IAIMPString</c> (the field name) and
    /// <c>IAIMPMLSortDirection</c> (the sort direction). The bridge implements
    /// the sort direction vtable and answers <c>QueryInterface(IID_IAIMPString)</c>
    /// with a native AIMP string that holds the field name.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class MlSortItemBridge : IAIMPMLSortDirectionNative, ICustomQueryInterface, IDisposable
    {
        private readonly IAimpSortItem _item;
        private IntPtr _fieldName;

        public MlSortItemBridge(IAimpSortItem item)
        {
            _item = item ?? throw new ArgumentNullException(nameof(item));
            _fieldName = AimpString.CreateNative(item.FieldName ?? string.Empty);
        }

        public CustomQueryInterfaceResult GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IUnknown || iid == AimpIids.IAIMPMLSortDirection)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPString)
            {
                if (_fieldName == IntPtr.Zero)
                {
                    return CustomQueryInterfaceResult.Failed;
                }

                ppv = AimpComHelper.AddRef(_fieldName);
                return CustomQueryInterfaceResult.Handled;
            }

            return CustomQueryInterfaceResult.Failed;
        }

        [PreserveSig]
        public int GetValue(out int value)
        {
            value = (int)_item.Value;
            return 0;
        }

        [PreserveSig]
        public int SetValue(int value)
        {
            _item.Value = (SortDirectionType)value;
            return 0;
        }

        public void Dispose()
        {
            var fieldName = _fieldName;
            _fieldName = IntPtr.Zero;

            AimpRuntime.Release(this);

            if (fieldName != IntPtr.Zero)
            {
                AimpComHelper.Release(fieldName);
            }
        }
    }
}