using System;
using AIMP.Internal.Runtime.Actions;
using AIMP.Internal.Runtime.AlbumArt;
using AIMP.Internal.Runtime.Collections;
using AIMP.Internal.Runtime.Common;
using AIMP.Internal.Runtime.Lyrics;
using AIMP.Internal.Runtime.MenuManager;
using AIMP.SDK;
using AIMP.SDK.Actions.Objects;
using AIMP.SDK.FileManager.Objects;
using AIMP.SDK.Lyrics.Objects;
using AIMP.SDK.MenuManager.Objects;
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Objects;
using V1Extension = AIMP.SDK.IAimpExtension;

namespace AIMP.Internal.Runtime.Core
{
    /// <summary>
    /// v1 <see cref="IAimpCore"/> over the managed host core.
    /// </summary>
    internal sealed class AimpCoreWrapper : AimpObjectWrapper, IAimpCore
    {
        private readonly AimpCore _core;

        public AimpCoreWrapper(AimpCore core)
        {
            _core = core ?? throw new ArgumentNullException(nameof(core));
        }

        public string GetPath(AimpCorePathType aimpCorePath)
        {
            try
            {
                return _core.GetPath(aimpCorePath);
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return null;
            }
        }

        public AimpActionResult SendMessage(
            AimpCoreMessageType message,
            int param,
            object objectParameter)
        {
            // IAIMPCore has no SendMessage in the current SDK headers.
            return new AimpActionResult(ActionResultType.NotImplemented);
        }

        public AimpActionResult RegisterExtension(V1Extension extension)
        {
            if (extension == null)
            {
                return AimpResult.Fail();
            }

            return AimpResult.From(AimpExtensionRegistrar.Register(_core, extension));
        }

        public AimpActionResult UnregisterExtension(V1Extension extension)
        {
            var hr = AimpExtensionRegistrar.Unregister(_core, extension);
            return AimpResult.From(hr);
        }

        public AimpActionResult<IAimpStream> CreateStream()
        {
            var pointer = CreateStreamObject();
            return pointer == IntPtr.Zero
                ? AimpResult.Fail<IAimpStream>()
                : AimpResult.Ok<IAimpStream>(new AimpStreamWrapper(pointer));
        }

        public AimpActionResult<IAimpObject> CreateObject<TAimpObject>() where TAimpObject : IAimpObject
        {
            try
            {
                var target = typeof(TAimpObject);

                if (target == typeof(IAimpMenuItem))
                {
                    return AimpResult.Ok<IAimpObject>(new AimpMenuItemWrapper());
                }

                if (target == typeof(IAimpAction))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPAction);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpActionWrapper(pointer));
                }

                if (target == typeof(IAimpConfigFile))
                {
                    AimpApiGuard.Require(6, 0, "IAimpConfigFile");
                    var pointer = CreateNativeObject(AimpIids.IAIMPConfigFile);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpConfigFileWrapper(pointer));
                }

                if (target == typeof(IAimpString))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPString);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpStringWrapper(new AimpString(pointer, null)));
                }

                if (target == typeof(IAimpStream))
                {
                    var pointer = CreateStreamObject();
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpStreamWrapper(pointer));
                }

                if (target == typeof(IAimpMemoryStream))
                {
                    // GetData exists only on the real memory stream object; the
                    // plain IAIMPStream fallback used by AIMP 5 must not be cast to it.
                    var pointer = CreateNativeObject(AimpIids.IAIMPMemoryStream);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpMemoryStreamWrapper(pointer));
                }

                if (target == typeof(IAimpFileInfo))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPFileInfo);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpFileInfoWrapper(pointer));
                }

                if (target == typeof(IAimpObjectList))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPObjectList);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpObjectListWrapper(new AimpObjectList(pointer)));
                }

                if (target == typeof(IAimpObjectList2))
                {
                    AimpApiGuard.Require(6, 0, "IAimpObjectList2");
                    var pointer = CreateNativeObject(AimpIids.IAIMPObjectList2);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpObjectListWrapper(new AimpObjectList(pointer)));
                }

                if (target == typeof(IAimpErrorInfo))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPErrorInfo);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpErrorInfoWrapper(pointer));
                }

                if (target == typeof(IAimpImage))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPImage);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpImageWrapper(pointer));
                }

                if (target == typeof(IAimpImageContainer))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPImageContainer);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpImageContainerWrapper(pointer));
                }

                if (target == typeof(IAimpLyrics))
                {
                    var pointer = CreateNativeObject(AimpIids.IAIMPLyrics);
                    return pointer == IntPtr.Zero
                        ? AimpResult.Fail<IAimpObject>()
                        : AimpResult.Ok<IAimpObject>(new AimpLyricsWrapper(pointer));
                }

                AimpLog.Write($"CreateObject<{target.FullName}> is not supported.");
                return AimpResult.Fail<IAimpObject>();
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return AimpResult.Fail<IAimpObject>();
            }
        }

        public AimpActionResult<IAimpObject> CreateObject(AimpObjectType objectType)
        {
            try
            {
                IntPtr pointer;

                switch (objectType)
                {
                    case AimpObjectType.AimpMenuItem:
                        return AimpResult.Ok<IAimpObject>(new AimpMenuItemWrapper());
                    case AimpObjectType.AimpStream:
                        pointer = CreateStreamObject();
                        break;
                    case AimpObjectType.AimpString:
                        pointer = CreateNativeObject(AimpIids.IAIMPString);
                        break;
                    case AimpObjectType.AimpFileInfo:
                        pointer = CreateNativeObject(AimpIids.IAIMPFileInfo);
                        break;
                    default:
                        AimpLog.Write($"CreateObject({objectType}) is not supported.");
                        return AimpResult.Fail<IAimpObject>();
                }

                if (pointer == IntPtr.Zero)
                {
                    return AimpResult.Fail<IAimpObject>();
                }

                switch (objectType)
                {
                    case AimpObjectType.AimpString:
                        return AimpResult.Ok<IAimpObject>(new AimpStringWrapper(new AimpString(pointer, null)));
                    case AimpObjectType.AimpStream:
                        return AimpResult.Ok<IAimpObject>(new AimpStreamWrapper(pointer));
                    case AimpObjectType.AimpFileInfo:
                        return AimpResult.Ok<IAimpObject>(new AimpFileInfoWrapper(pointer));
                    default:
                        return AimpResult.Fail<IAimpObject>();
                }
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return AimpResult.Fail<IAimpObject>();
            }
        }

        /// <summary>
        /// Creates a native object without throwing for unavailable IIDs.
        /// </summary>
        private IntPtr CreateNativeObject(Guid iid, bool logFailure = true)
        {
            var hr = _core.TryCreateObject(iid, out var pointer);
            if (hr >= 0 && pointer != IntPtr.Zero)
            {
                return pointer;
            }

            if (logFailure)
            {
                AimpLog.Write(
                    $"CreateObject({iid.ToString("D")}) is not available (HRESULT 0x{hr.ToString("X8")}).");
            }

            return IntPtr.Zero;
        }

        /// <summary>
        /// AIMP 6 exposes IAIMPMemoryStream; older versions create the base
        /// IAIMPStream object instead.
        /// </summary>
        private IntPtr CreateStreamObject()
        {
            var pointer = CreateNativeObject(AimpIids.IAIMPMemoryStream, false);
            return pointer != IntPtr.Zero
                ? pointer
                : CreateNativeObject(AimpIids.IAIMPStream);
        }

        protected override void OnDispose()
        {
        }
    }
}