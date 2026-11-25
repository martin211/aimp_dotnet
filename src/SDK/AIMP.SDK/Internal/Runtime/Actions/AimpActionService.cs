using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Actions;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Actions;
using AIMP.SDK.Actions.Objects;

namespace AIMP.Internal.Runtime.Actions;

/// <summary>
/// v1 <see cref="IAimpServiceActionManager"/>.
/// </summary>
internal sealed class AimpActionService : AimpObjectWrapper, IAimpServiceActionManager
{
    private readonly AimpCore _core;
    private readonly IAimpServiceActionManagerNative _native;

    public AimpActionService(AimpCore core)
    {
        _core = core;
        _native = core?.GetService<IAimpServiceActionManagerNative>(AimpIids.IAIMPServiceActionManager);
    }

    public bool IsExists => _native != null;

    public AimpActionResult<IAimpAction> GetById(string id)
    {
        if (_native == null)
        {
            return AimpResult.Fail<IAimpAction>();
        }

        var pointer = AimpString.CreateNative(id);

        try
        {
            return _native.GetByID(pointer, out var action) < 0 || action == IntPtr.Zero
                ? AimpResult.Fail<IAimpAction>()
                : AimpResult.Ok<IAimpAction>(new AimpActionWrapper(action));
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public int MakeHotkey(System.Windows.Input.ModifierKeys modifiers, uint key)
    {
        if (_native == null)
        {
            return 0;
        }

        return _native.MakeHotkey((ushort)modifiers, (ushort)key);
    }

    public AimpActionResult Register(IAimpAction action)
    {
        if (action == null)
        {
            throw new ArgumentNullException(nameof(action));
        }

        AimpLog.Write($"ActionManager.Register: id='{action.Id}', name='{action.Name}'.");

        if (string.IsNullOrEmpty(action.Id))
        {
            throw new ArgumentNullException(nameof(action), "Action id cannot be empty.");
        }

        if (string.IsNullOrEmpty(action.Name))
        {
            throw new ArgumentNullException(nameof(action), "Action name cannot be empty.");
        }

        var native = action as IAimpNativeObject;
        if (native == null)
        {
            return AimpResult.Fail();
        }

        var pointer = native.NativePointer;

        try
        {
            return AimpResult.From(
                _core.RegisterExtension(AimpIids.IAIMPServiceActionManager, pointer));
        }
        finally
        {
            AimpComHelper.Release(pointer);
        }
    }

    public AimpActionResult Register(System.Collections.Generic.ICollection<IAimpAction> actions)
    {
        if (actions == null)
        {
            return AimpResult.Fail();
        }

        foreach (var action in actions)
        {
            var result = Register(action);

            if (result.ResultType != ActionResultType.OK)
            {
                return result;
            }
        }

        return AimpResult.Ok();
    }

    public IAimpAction CreateAction()
    {
        var pointer = _core.CreateObject(AimpIids.IAIMPAction);
        return new AimpActionWrapper(pointer);
    }

    protected override void OnDispose()
    {
        if (_native != null)
        {
            Marshal.FinalReleaseComObject(_native);
        }
    }
}