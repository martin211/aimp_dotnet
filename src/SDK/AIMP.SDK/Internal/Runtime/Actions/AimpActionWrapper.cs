using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Actions;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Actions.Objects;

namespace AIMP.Internal.Runtime.Actions;

/// <summary>
/// v1 <see cref="IAimpAction"/> over the native <c>IAIMPAction</c>.
/// </summary>
internal sealed class AimpActionWrapper : AimpObjectWrapper, IAimpAction, IAimpNativeObject
{
    private readonly IAimpActionNative _native;
    private readonly AimpPropertyBag _properties;
    private readonly IntPtr _pointer;
    private EventHandler _onExecute;
    private IntPtr _eventPointer;

    public AimpActionWrapper(IntPtr ownedPointer)
    {
        _pointer = ownedPointer;
        _native = AimpComHelper.Wrap<IAimpActionNative>(ownedPointer);
        _properties = new AimpPropertyBag((IAIMPPropertyListNative)_native);
    }

    public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

    public string Id
    {
        get => _properties.GetString(AimpPropId.ActionId);
        set => _properties.SetString(AimpPropId.ActionId, value);
    }

    public string CustomData
    {
        get => _properties.GetString(AimpPropId.ActionCustom);
        set => _properties.SetString(AimpPropId.ActionCustom, value);
    }

    public string Name
    {
        get => _properties.GetString(AimpPropId.ActionName);
        set => _properties.SetString(AimpPropId.ActionName, value);
    }

    public string GroupName
    {
        get => _properties.GetString(AimpPropId.ActionGroupName);
        set => _properties.SetString(AimpPropId.ActionGroupName, value);
    }

    public bool Enabled
    {
        get => _properties.GetBool(AimpPropId.ActionEnabled, true);
        set => _properties.SetBool(AimpPropId.ActionEnabled, value);
    }

    public int DefaultLocalHotKey
    {
        get => _properties.GetInt32(AimpPropId.ActionDefaultLocalHotKey);
        set => _properties.SetInt32(AimpPropId.ActionDefaultLocalHotKey, value);
    }

    public int DefaultGlobalHotKey
    {
        get => _properties.GetInt32(AimpPropId.ActionDefaultGlobalHotKey);
        set => _properties.SetInt32(AimpPropId.ActionDefaultGlobalHotKey, value);
    }

    public int AlternativeGlobalHotKey
    {
        get => _properties.GetInt32(AimpPropId.ActionDefaultGlobalHotKey2);
        set => _properties.SetInt32(AimpPropId.ActionDefaultGlobalHotKey2, value);
    }

    public event EventHandler OnExecute
    {
        add
        {
            _onExecute += value;

            if (_eventPointer == IntPtr.Zero)
            {
                _eventPointer = AimpActionEventBridge.CreatePointer(() => _onExecute?.Invoke(this, EventArgs.Empty));
                _properties.SetObject(AimpPropId.ActionEvent, _eventPointer);
            }
        }
        remove
        {
            _onExecute -= value;

            if (_onExecute == null && _eventPointer != IntPtr.Zero)
            {
                _properties.SetObject(AimpPropId.ActionEvent, IntPtr.Zero);
                AimpComHelper.Release(_eventPointer);
                _eventPointer = IntPtr.Zero;
            }
        }
    }

    protected override void OnDispose()
    {
        _properties.Dispose();
        Marshal.FinalReleaseComObject(_native);
    }
}