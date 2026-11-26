using System;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.Core;
using AIMP.SDK.MessageDispatcher;

namespace AIMP.Internal
{
    /// <summary>
    /// New, C++/CLI free view of <c>IAIMPCore</c>.
    ///
    /// Everything is pointer based: services are obtained with a plain
    /// QueryInterface, so a plugin can declare its own <c>[ComImport]</c>
    /// interface for any AIMP service and use <see cref="GetService{T}"/>.
    ///
    /// The player calls providers on background threads. Marshalling an RCW of
    /// the core across apartments fails (the objects are not agile), so the
    /// methods of the core are invoked through its vtable directly.
    /// </summary>
    internal sealed class AimpCore
    {
        // IAIMPCore (apiCore.h): 0..2 = IUnknown, then
        // CreateObject, GetPath, RegisterExtension, RegisterService, UnregisterExtension.
        private const int SlotCreateObject = 3;
        private const int SlotGetPath = 4;
        private const int SlotRegisterExtension = 5;
        private const int SlotUnregisterExtension = 7;

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int CreateObjectHandler(IntPtr self, ref Guid iid, out IntPtr instance);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int GetPathHandler(IntPtr self, int pathId, out IntPtr value);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int RegisterExtensionHandler(IntPtr self, ref Guid serviceIid, IntPtr extension);

        [UnmanagedFunctionPointer(CallingConvention.Winapi)]
        private delegate int UnregisterExtensionHandler(IntPtr self, IntPtr extension);

        private readonly CreateObjectHandler _createObject;
        private readonly GetPathHandler _getPath;
        private readonly RegisterExtensionHandler _registerExtension;
        private readonly UnregisterExtensionHandler _unregisterExtension;
        private IAIMPCoreNative _core;

        public AimpCore(IntPtr native)
        {
            Native = native;
            _createObject = GetMethod<CreateObjectHandler>(native, SlotCreateObject);
            _getPath = GetMethod<GetPathHandler>(native, SlotGetPath);
            _registerExtension = GetMethod<RegisterExtensionHandler>(native, SlotRegisterExtension);
            _unregisterExtension = GetMethod<UnregisterExtensionHandler>(native, SlotUnregisterExtension);
        }

        /// <summary>
        /// Raw <c>IAIMPCore*</c> pointer owned by AIMP.
        /// </summary>
        public IntPtr Native { get; }

        /// <summary>
        /// Native projection of the core for advanced scenarios. It is bound to
        /// the apartment that created it; prefer the methods of this class.
        /// </summary>
        public IAIMPCoreNative NativeCore =>
            _core ?? (_core = (IAIMPCoreNative)Marshal.GetObjectForIUnknown(Native));

        /// <summary>
        /// Creates a native AIMP object and returns its interface pointer.
        /// </summary>
        public IntPtr CreateObject(Guid iid)
        {
            var hr = TryCreateObject(iid, out var instance);
            if (hr < 0)
            {
                Marshal.ThrowExceptionForHR(hr);
            }

            return instance;
        }

        /// <summary>
        /// Tries to create a native AIMP object and returns the raw HRESULT.
        /// Unlike <see cref="CreateObject(Guid)"/> it does not throw.
        /// </summary>
        public int TryCreateObject(Guid iid, out IntPtr instance)
        {
            return _createObject(Native, ref iid, out instance);
        }

        /// <summary>
        /// Creates a native AIMP object and wraps it into the given interface.
        /// </summary>
        public T CreateObject<T>(Guid iid) where T : class
        {
            return AimpComHelper.Wrap<T>(CreateObject(iid));
        }

        /// <summary>
        /// Resolves one of the player system folders.
        /// </summary>
        public string GetPath(AimpCorePathType path)
        {
            var hr = _getPath(Native, (int)path, out var value);
            return hr < 0 ? null : AimpString.ReadAndRelease(value);
        }

        /// <summary>
        /// Creates a new native AIMP string.
        /// </summary>
        public AimpString CreateString(string value)
        {
            return new AimpString(CreateObject(AimpIids.IAIMPString), value);
        }

        /// <summary>
        /// Queries any AIMP service. <typeparamref name="T"/> must be a
        /// <c>[ComImport]</c> interface whose vtable matches the SDK header.
        /// Returns <c>null</c> when the service is not available.
        /// </summary>
        public T GetService<T>(Guid iid) where T : class
        {
            var hr = Marshal.QueryInterface(Native, ref iid, out var instance);
            if (hr < 0)
            {
                return null;
            }

            try
            {
                return (T)Marshal.GetTypedObjectForIUnknown(instance, typeof(T));
            }
            finally
            {
                Marshal.Release(instance);
            }
        }

        /// <summary>
        /// Registers an extension object. <paramref name="serviceIid"/> is the
        /// IID of the service that owns the extension point, not the extension
        /// interface itself.
        /// </summary>
        public int RegisterExtension(Guid serviceIid, IntPtr extension)
        {
            return _registerExtension(Native, ref serviceIid, extension);
        }

        /// <summary>
        /// Unregisters a previously registered extension.
        /// </summary>
        public int UnregisterExtension(IntPtr extension)
        {
            return _unregisterExtension(Native, extension);
        }

        private static T GetMethod<T>(IntPtr instance, int slot) where T : class
        {
            var vtable = Marshal.ReadIntPtr(instance);
            var address = Marshal.ReadIntPtr(vtable, slot * IntPtr.Size);
            return (T)(object)Marshal.GetDelegateForFunctionPointer(address, typeof(T));
        }
    }
}