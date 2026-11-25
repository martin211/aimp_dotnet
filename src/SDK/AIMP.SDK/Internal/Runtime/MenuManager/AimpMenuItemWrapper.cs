using System;
using System.Drawing;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.MenuManager;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Actions;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.MenuManager.Objects;

namespace AIMP.Internal.Runtime.MenuManager
{
    /// <summary>
    /// v1 <see cref="IAimpMenuItem"/> over the native <c>IAIMPMenuItem</c>.
    /// </summary>
    internal sealed class AimpMenuItemWrapper : AimpObjectWrapper, IAimpMenuItem, IAimpNativeObject
    {
        private readonly IAIMPMenuItemNative _native;
        private readonly AimpPropertyBag _properties;
        private readonly IntPtr _pointer;
        private AimpActionWrapper _action;
        private EventHandler _onExecute;
        private EventHandler _onShow;
        private IntPtr _executePointer;
        private IntPtr _showPointer;

        /// <summary>
        /// Creates a new menu item object.
        /// </summary>
        public AimpMenuItemWrapper()
            : this(AimpRuntime.RequireCore().CreateObject(AimpIids.IAIMPMenuItem))
        {
        }

        /// <summary>
        /// Wraps a pointer taking ownership of the reference.
        /// </summary>
        public AimpMenuItemWrapper(IntPtr ownedPointer)
        {
            _pointer = ownedPointer;
            _native = AimpComHelper.Wrap<IAIMPMenuItemNative>(ownedPointer);
            _properties = new AimpPropertyBag((IAIMPPropertyListNative)(object)_native);
        }

        public IntPtr NativePointer => AimpComHelper.AddRef(_pointer);

        private IAIMPMenuItemNative Native => _native;

        public string Custom
        {
            get => _properties.GetString(AimpPropId.MenuItemCustom);
            set => _properties.SetString(AimpPropId.MenuItemCustom, value);
        }

        public IAimpAction Action
        {
            get
            {
                if (_action != null)
                {
                    return _action;
                }

                var pointer = _properties.GetObjectPointer(
                    AimpPropId.MenuItemAction,
                    AimpIids.IAIMPAction);

                if (pointer == IntPtr.Zero)
                {
                    return null;
                }

                _action = new AimpActionWrapper(pointer);
                return _action;
            }
            set
            {
                _action = value as AimpActionWrapper;

                var pointer = (value as IAimpNativeObject)?.NativePointer ?? IntPtr.Zero;

                try
                {
                    _properties.SetObject(AimpPropId.MenuItemAction, pointer);
                }
                finally
                {
                    AimpComHelper.Release(pointer);
                }
            }
        }

        public string Id
        {
            get => _properties.GetString(AimpPropId.MenuItemId);
            set => _properties.SetString(AimpPropId.MenuItemId, value);
        }

        public string Name
        {
            get => _properties.GetString(AimpPropId.MenuItemName);
            set => _properties.SetString(AimpPropId.MenuItemName, value);
        }

        public bool Checked
        {
            get => _properties.GetBool(AimpPropId.MenuItemChecked);
            set => _properties.SetBool(AimpPropId.MenuItemChecked, value);
        }

        public bool Enabled
        {
            get => _properties.GetBool(AimpPropId.MenuItemEnabled, true);
            set => _properties.SetBool(AimpPropId.MenuItemEnabled, value);
        }

        public Bitmap Glyph
        {
            get => null;
            set
            {
                // Bitmap -> IAIMPImage conversion is not projected yet.
            }
        }

        public IAimpMenuItem Parent
        {
            get
            {
                var pointer = _properties.GetObjectPointer(
                    AimpPropId.MenuItemParent,
                    AimpIids.IAIMPMenuItem);

                return pointer == IntPtr.Zero ? null : new AimpMenuItemWrapper(pointer);
            }
            set
            {
                var pointer = (value as IAimpNativeObject)?.NativePointer ?? IntPtr.Zero;

                try
                {
                    _properties.SetObject(AimpPropId.MenuItemParent, pointer);
                }
                finally
                {
                    AimpComHelper.Release(pointer);
                }
            }
        }

        public MenuItemStyle Style
        {
            get => (MenuItemStyle)_properties.GetInt32(AimpPropId.MenuItemStyle);
            set => _properties.SetInt32(AimpPropId.MenuItemStyle, (int)value);
        }

        public bool Visible
        {
            get => _properties.GetBool(AimpPropId.MenuItemVisible, true);
            set => _properties.SetBool(AimpPropId.MenuItemVisible, value);
        }

        public bool IsDefault
        {
            get => _properties.GetBool(AimpPropId.MenuItemDefault);
            set => _properties.SetBool(AimpPropId.MenuItemDefault, value);
        }

        public int Shortcut
        {
            get => _properties.GetInt32(AimpPropId.MenuItemShortcut);
            set => _properties.SetInt32(AimpPropId.MenuItemShortcut, value);
        }

        public AimpActionResult DeleteChildren()
        {
            return AimpResult.From(_native.DeleteChildren());
        }

        /// <summary>
        /// Attaches the item to a raw native parent menu item.
        /// </summary>
        internal void SetParentPointer(IntPtr parent)
        {
            _properties.SetObject(AimpPropId.MenuItemParent, parent);
        }

        public event EventHandler OnExecute
        {
            add
            {
                _onExecute += value;

                if (_executePointer == IntPtr.Zero)
                {
                    _executePointer =
                        AimpActionEventBridge.CreatePointer(() => _onExecute?.Invoke(this, EventArgs.Empty));
                    _properties.SetObject(AimpPropId.MenuItemEvent, _executePointer);
                }
            }
            remove
            {
                _onExecute -= value;

                if (_onExecute == null && _executePointer != IntPtr.Zero)
                {
                    _properties.SetObject(AimpPropId.MenuItemEvent, IntPtr.Zero);
                    AimpComHelper.Release(_executePointer);
                    _executePointer = IntPtr.Zero;
                }
            }
        }

        public event EventHandler OnShow
        {
            add
            {
                _onShow += value;

                if (_showPointer == IntPtr.Zero)
                {
                    _showPointer = AimpActionEventBridge.CreatePointer(() => _onShow?.Invoke(this, EventArgs.Empty));
                    _properties.SetObject(AimpPropId.MenuItemEventOnShow, _showPointer);
                }
            }
            remove
            {
                _onShow -= value;

                if (_onShow == null && _showPointer != IntPtr.Zero)
                {
                    _properties.SetObject(AimpPropId.MenuItemEventOnShow, IntPtr.Zero);
                    AimpComHelper.Release(_showPointer);
                    _showPointer = IntPtr.Zero;
                }
            }
        }

        protected override void OnDispose()
        {
            _properties.Dispose();

            if (_native != null)
            {
                Marshal.FinalReleaseComObject(_native);
            }

            if (_executePointer != IntPtr.Zero)
            {
                AimpComHelper.Release(_executePointer);
                _executePointer = IntPtr.Zero;
            }

            if (_showPointer != IntPtr.Zero)
            {
                AimpComHelper.Release(_showPointer);
                _showPointer = IntPtr.Zero;
            }
        }
    }
}