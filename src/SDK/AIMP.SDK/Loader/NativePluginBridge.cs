using System;
using System.Runtime.InteropServices;
using AIMP.Internal;
using AIMP.Internal.Bridges;
using AIMP.Internal.Native.Plugin;
using AIMP.Internal.Runtime.Core;
using AIMP.SDK;

namespace AIMP.Loader
{
    /// <summary>
    /// Bridges the managed v1-style plugin to the native <c>IAIMPPlugin</c>
    /// vtable. An instance of this class is what AIMP actually talks to.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class NativePluginBridge : IAimpPluginNative, IAIMPExternalSettingsDialogNative, ICustomQueryInterface
    {
        private readonly AimpPlugin _plugin;
        private readonly AimpPluginAttribute _attribute;
        private readonly IntPtr[] _infoStrings = new IntPtr[4];

        private AimpCore _core;
        private AimpPlayer _player;

        public NativePluginBridge(AimpPlugin plugin, AimpPluginAttribute attribute)
        {
            _plugin = plugin ?? throw new ArgumentNullException(nameof(plugin));
            _attribute = attribute ?? new AimpPluginAttribute(plugin.GetType().Name, string.Empty, string.Empty);
        }

        IntPtr IAimpPluginNative.InfoGet(int index)
        {
            if (index < 0 || index >= _infoStrings.Length)
            {
                return IntPtr.Zero;
            }

            lock (_infoStrings)
            {
                if (_infoStrings[index] == IntPtr.Zero)
                {
                    _infoStrings[index] = Marshal.StringToHGlobalUni(GetInfoText(index) ?? string.Empty);
                }

                return _infoStrings[index];
            }
        }

        uint IAimpPluginNative.InfoGetCategories()
        {
            return (uint)_attribute.AimpPluginType;
        }

        int IAimpPluginNative.Initialize(IntPtr core)
        {
            try
            {
                AimpLog.Write($"Initialize: plugin '{_attribute.Name}'");

                if (core == IntPtr.Zero)
                {
                    throw new ArgumentException("AIMP core pointer is required.", nameof(core));
                }

                _core = new AimpCore(core);
                AimpRuntime.Initialize(_core);

                _player = new AimpPlayer(_core);

                try
                {
                    var version = AimpRuntime.DetectVersion(_player.ServiceVersionInfo);
                    AimpRuntime.SetVersion(version);
                    AimpLog.Write($"AIMP: {version}");
                }
                catch (Exception versionException)
                {
                    AimpLog.Write(versionException);
                }

                _plugin.OnPreInitialize(_player);
                _plugin.OnInitialize(_player, _plugin.GetHashCode());

                return 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return unchecked((int)ActionResultType.Fail);
            }
        }

        int IAimpPluginNative.Finalize()
        {
            try
            {
                AimpLog.Write($"Finalize: plugin '{_attribute.Name}'");
                _plugin.OnDispose();
                return 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return unchecked((int)ActionResultType.Fail);
            }
            finally
            {
                _player = null;
                _core = null;
                FreeInfoStrings();
                AimpRuntime.Shutdown();
                AimpLog.Close();
            }
        }

        void IAimpPluginNative.SystemNotification(int notifyId, IntPtr data)
        {
            AimpLog.Write($"SystemNotification: {notifyId}");
        }

        void IAIMPExternalSettingsDialogNative.Show(IntPtr parentWindow)
        {
            Safe.Run(() =>
            {
                var dialog = _plugin as IAimpExternalSettingsDialog;
                dialog?.Show(parentWindow);
            });
        }

        CustomQueryInterfaceResult ICustomQueryInterface.GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IAIMPExternalSettingsDialog)
            {
                // Only expose the external settings dialog when the plugin
                // actually implements it; otherwise AIMP must get E_NOINTERFACE.
                return _plugin is IAimpExternalSettingsDialog
                    ? CustomQueryInterfaceResult.NotHandled
                    : CustomQueryInterfaceResult.Failed;
            }

            return CustomQueryInterfaceResult.NotHandled;
        }

        private string GetInfoText(int index)
        {
            switch (index)
            {
                case 0:
                    return _attribute.Name;
                case 1:
                    return _attribute.Author;
                case 2:
                    return string.IsNullOrEmpty(_attribute.Description)
                        ? _attribute.Version
                        : _attribute.Description;
                case 3:
                    return string.IsNullOrEmpty(_attribute.FullDescription)
                        ? _attribute.Description
                        : _attribute.FullDescription;
                default:
                    return null;
            }
        }

        private void FreeInfoStrings()
        {
            lock (_infoStrings)
            {
                for (var i = 0; i < _infoStrings.Length; i++)
                {
                    if (_infoStrings[i] == IntPtr.Zero)
                    {
                        continue;
                    }

                    Marshal.FreeHGlobal(_infoStrings[i]);
                    _infoStrings[i] = IntPtr.Zero;
                }
            }
        }
    }
}