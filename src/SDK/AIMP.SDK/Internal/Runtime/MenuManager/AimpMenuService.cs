using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MenuManager;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.MenuManager;
using AIMP.SDK.MenuManager.Objects;

namespace AIMP.Internal.Runtime.MenuManager;

/// <summary>
/// v1 <see cref="IAimpServiceMenuManager"/>.
/// </summary>
internal sealed class AimpMenuService : AimpObjectWrapper, IAimpServiceMenuManager
{
    private readonly AimpCore _core;
    private readonly IAIMPServiceMenuManagerNative _native;

    public AimpMenuService(AimpCore core)
    {
        _core = core;
        _native = core?.GetService<IAIMPServiceMenuManagerNative>(AimpIids.IAIMPServiceMenuManager);
    }

    public AimpMenuService(IntPtr borrowedPointer)
    {
        _native = AimpComHelper.WrapBorrowed<IAIMPServiceMenuManagerNative>(borrowedPointer);
    }

    public bool IsExists => _native != null;

    public AimpActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem item)
    {
        if (_native == null || !(item is IAimpNativeObject native))
        {
            return AimpResult.Fail();
        }

        if (_native.GetBuiltIn((int)parentMenuType, out var parent) < 0 || parent == IntPtr.Zero)
        {
            return AimpResult.Fail();
        }

        var itemPointer = native.NativePointer;

        try
        {
            (item as AimpMenuItemWrapper)?.SetParentPointer(parent);

            var core = _core ?? AimpRuntime.RequireCore();
            return AimpResult.From(core.RegisterExtension(AimpIids.IAIMPServiceMenuManager, itemPointer));
        }
        finally
        {
            AimpComHelper.Release(itemPointer);
            AimpComHelper.Release(parent);
        }
    }

    public AimpActionResult Add(IAimpMenuItem item)
    {
        if (!(item is IAimpNativeObject native))
        {
            return AimpResult.Fail();
        }

        var core = _core ?? AimpRuntime.RequireCore();
        var pointer = native.NativePointer;

        try
        {
            return AimpResult.From(core.RegisterExtension(AimpIids.IAIMPServiceMenuManager, pointer));
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult Delete(IAimpMenuItem item)
    {
        return item == null ? AimpResult.Fail() : Delete(item.Id);
    }

    public AimpActionResult Delete(string id)
    {
        if (_native == null)
        {
            return AimpResult.Fail();
        }

        var pointer = AimpString.CreateNative(id);

        try
        {
            if (_native.GetByID(pointer, out var item) < 0 || item == IntPtr.Zero)
            {
                return AimpResult.Fail();
            }

            try
            {
                var core = _core ?? AimpRuntime.RequireCore();
                return AimpResult.From(core.UnregisterExtension(item));
            }
            finally
            {
                AimpComHelper.Release(item);
            }
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult<IAimpMenuItem> GetById(string id)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpMenuItem>();
        }

        var pointer = AimpString.CreateNative(id);

        try
        {
            return _native.GetByID(pointer, out var item) < 0 || item == IntPtr.Zero
                ? AimpResult.Fail<IAimpMenuItem>()
                : AimpResult.Ok<IAimpMenuItem>(new AimpMenuItemWrapper(item));
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult<IAimpMenuItem> GetBuiltIn(ParentMenuType menuType)
    {
        return _native == null ||
               _native.GetBuiltIn((int)menuType, out var item) < 0 ||
               item == IntPtr.Zero
            ? AimpResult.Fail<IAimpMenuItem>()
            : AimpResult.Ok<IAimpMenuItem>(new AimpMenuItemWrapper(item));
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}