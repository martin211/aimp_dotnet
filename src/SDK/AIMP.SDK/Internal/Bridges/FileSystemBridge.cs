using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using AIMP.Internal.Native.FileManager;
using AIMP.Internal.Native.Objects;
using AIMP.SDK;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Commands;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.Internal.Bridges
{
    /// <summary>
    /// Bridges <see cref="IAimpExtensionFileSystem"/> (plus the optional
    /// command interfaces) to the native file system vtables.
    /// </summary>
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.None)]
    internal sealed class FileSystemBridge :
        IAIMPExtensionFileSystemNative,
        IAIMPFileSystemCommandOpenFileFolderNative,
        IAIMPFileSystemCommandFileInfoNative,
        IAIMPFileSystemCommandFileInfoLegacyNative,
        IAIMPFileSystemCommandCopyToClipboardNative,
        IAIMPFileSystemCommandDeleteNative,
        IAIMPFileSystemCommandDropSourceNative,
        IAIMPFileSystemCommandStreamingNative,
        ICustomQueryInterface
    {
        private readonly IAimpExtensionFileSystem _fileSystem;
        private readonly IAimpFileSystemCommandOpenFileFolder _openFileFolder;
        private readonly IAimpFileSystemCommandFileInfo _fileInfo;
        private readonly IAimpFileSystemCommandCopyToClipboard _copyToClipboard;
        private readonly IAimpFileSystemCommandDelete _delete;
        private readonly IAimpFileSystemCommandDropSource _dropSource;
        private readonly IAimpFileSystemCommandStreaming _streaming;

        public FileSystemBridge(IAimpExtensionFileSystem fileSystem)
        {
            _fileSystem = fileSystem ?? throw new ArgumentNullException(nameof(fileSystem));
            _openFileFolder = fileSystem as IAimpFileSystemCommandOpenFileFolder;
            _fileInfo = fileSystem as IAimpFileSystemCommandFileInfo;
            _copyToClipboard = fileSystem as IAimpFileSystemCommandCopyToClipboard;
            _delete = fileSystem as IAimpFileSystemCommandDelete;
            _dropSource = fileSystem as IAimpFileSystemCommandDropSource;
            _streaming = fileSystem as IAimpFileSystemCommandStreaming;
        }

        public CustomQueryInterfaceResult GetInterface(ref Guid iid, out IntPtr ppv)
        {
            ppv = IntPtr.Zero;

            if (iid == AimpIids.IUnknown || iid == AimpIids.IAIMPExtensionFileSystem)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPFileSystemCommandOpenFileFolder && _openFileFolder != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if ((iid == AimpIids.IAIMPFileSystemCommandFileInfo ||
                 iid == AimpIids.IAIMPFileSystemCommandFileInfoLegacy) && _fileInfo != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPFileSystemCommandCopyToClipboard && _copyToClipboard != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPFileSystemCommandDelete && _delete != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPFileSystemCommandDropSource && _dropSource != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            if (iid == AimpIids.IAIMPFileSystemCommandStreaming && _streaming != null)
            {
                return CustomQueryInterfaceResult.NotHandled;
            }

            return CustomQueryInterfaceResult.Failed;
        }

        #region IAIMPExtensionFileSystem (IAIMPPropertyList)

        [PreserveSig]
        public void BeginUpdate()
        {
        }

        [PreserveSig]
        public void EndUpdate()
        {
        }

        [PreserveSig]
        public int Reset()
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int GetValueAsFloat(int propertyId, out double value)
        {
            value = 0;
            return Safe.E_NOTIMPL;
        }

        [PreserveSig]
        public int GetValueAsInt32(int propertyId, out int value)
        {
            value = 0;

            if (propertyId == AimpPropId.FileSystemReadOnly)
            {
                value = _fileSystem.ReadOnly ? 1 : 0;
                return Safe.S_OK;
            }

            return Safe.E_NOTIMPL;
        }

        [PreserveSig]
        public int GetValueAsInt64(int propertyId, out long value)
        {
            value = 0;
            return Safe.E_NOTIMPL;
        }

        [PreserveSig]
        public int GetValueAsObject(int propertyId, ref Guid iid, out IntPtr value)
        {
            value = IntPtr.Zero;

            if (propertyId != AimpPropId.FileSystemScheme)
            {
                return Safe.E_NOTIMPL;
            }

            value = AimpString.CreateNative(_fileSystem.Schema ?? string.Empty);
            return value == IntPtr.Zero ? Safe.E_FAIL : Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsFloat(int propertyId, double value)
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsInt32(int propertyId, int value)
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsInt64(int propertyId, long value)
        {
            return Safe.S_OK;
        }

        [PreserveSig]
        public int SetValueAsObject(int propertyId, IntPtr value)
        {
            return Safe.S_OK;
        }

        #endregion

        #region IAIMPFileSystemCommandOpenFileFolder

        [PreserveSig]
        int IAIMPFileSystemCommandOpenFileFolderNative.CanProcess(IntPtr fileName)
        {
            try
            {
                return _openFileFolder.CanProcess(AimpString.Read(fileName)).ResultType ==
                       ActionResultType.OK
                    ? 1
                    : 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }

        [PreserveSig]
        int IAIMPFileSystemCommandOpenFileFolderNative.Process(IntPtr fileName)
        {
            return Safe.Run(() => ToHResult(_openFileFolder.Process(AimpString.Read(fileName))));
        }

        #endregion

        #region IAIMPFileSystemCommandFileInfo

        [PreserveSig]
        int IAIMPFileSystemCommandFileInfoNative.GetFileAttrs(IntPtr fileName, IntPtr attrs)
        {
            return Safe.Run(() =>
            {
                var result = _fileInfo.GetFileAttrs(AimpString.Read(fileName));
                if (result.ResultType != ActionResultType.OK)
                {
                    return ToHResult(result);
                }

                if (attrs == IntPtr.Zero)
                {
                    return Safe.E_POINTER;
                }

                var managed = result.Result;
                var native = new TAIMPFileAttributes
                {
                    Attributes = (uint)managed.Attributes,
                    TimeCreation = managed.TimeCreation,
                    TimeLastAccess = managed.TimeLastAccess,
                    TimeLastWrite = managed.TimeLastWrite
                };

                Marshal.StructureToPtr(native, attrs, false);
                return Safe.S_OK;
            });
        }

        [PreserveSig]
        int IAIMPFileSystemCommandFileInfoNative.GetFileSize(IntPtr fileName, out long size)
        {
            var value = 0L;

            var hr = Safe.Run(() =>
            {
                var result = _fileInfo.GetFileSize(AimpString.Read(fileName));
                if (result.ResultType == ActionResultType.OK)
                {
                    value = result.Result;
                }

                return ToHResult(result);
            });

            size = value;
            return hr;
        }

        [PreserveSig]
        int IAIMPFileSystemCommandFileInfoNative.IsFileExists(IntPtr fileName)
        {
            try
            {
                return _fileInfo.IsFileExists(AimpString.Read(fileName)).ResultType == ActionResultType.OK
                    ? 1
                    : 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }

        [PreserveSig]
        int IAIMPFileSystemCommandFileInfoLegacyNative.GetFileAttrs(IntPtr fileName, IntPtr attrs)
        {
            return ((IAIMPFileSystemCommandFileInfoNative)this).GetFileAttrs(fileName, attrs);
        }

        [PreserveSig]
        int IAIMPFileSystemCommandFileInfoLegacyNative.GetFileSize(IntPtr fileName, out long size)
        {
            return ((IAIMPFileSystemCommandFileInfoNative)this).GetFileSize(fileName, out size);
        }

        [PreserveSig]
        int IAIMPFileSystemCommandFileInfoLegacyNative.IsFileExists(IntPtr fileName)
        {
            return ((IAIMPFileSystemCommandFileInfoNative)this).IsFileExists(fileName);
        }

        #endregion

        #region IAIMPFileSystemCommandCopyToClipboard

        [PreserveSig]
        int IAIMPFileSystemCommandCopyToClipboardNative.CopyToClipboard(IntPtr files)
        {
            return Safe.Run(() =>
            {
                var items = new List<string>();

                using (var list = new AimpObjectList(AimpComHelper.AddRef(files)))
                {
                    for (var i = 0; i < list.Count; i++)
                    {
                        items.Add(list.GetString(i));
                    }
                }

                return ToHResult(_copyToClipboard.CopyToClipboard(items));
            });
        }

        #endregion

        #region IAIMPFileSystemCommandDelete

        [PreserveSig]
        int IAIMPFileSystemCommandDeleteNative.CanProcess(IntPtr fileName)
        {
            try
            {
                return _delete.CanProcess(AimpString.Read(fileName)).ResultType == ActionResultType.OK ? 1 : 0;
            }
            catch (Exception exception)
            {
                AimpLog.Write(exception);
                return 0;
            }
        }

        [PreserveSig]
        int IAIMPFileSystemCommandDeleteNative.Process(IntPtr fileName)
        {
            return Safe.Run(() => ToHResult(_delete.Process(AimpString.Read(fileName))));
        }

        #endregion

        #region IAIMPFileSystemCommandDropSource

        [PreserveSig]
        int IAIMPFileSystemCommandDropSourceNative.CreateStream(IntPtr fileName, out IntPtr stream)
        {
            var value = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var result = _dropSource.CreateStream(AimpString.Read(fileName));
                if (result.ResultType != ActionResultType.OK || result.Result == null)
                {
                    return ToHResult(result);
                }

                value = AimpBridgeHelper.GetStreamPointer(result.Result);
                return Safe.S_OK;
            });

            stream = value;
            return hr;
        }

        #endregion

        #region IAIMPFileSystemCommandStreaming

        [PreserveSig]
        int IAIMPFileSystemCommandStreamingNative.CreateStream(
            IntPtr fileName,
            long offset,
            long size,
            uint flags,
            out IntPtr stream)
        {
            var value = IntPtr.Zero;

            var hr = Safe.Run(() =>
            {
                var result = _streaming.CreateStream(
                    AimpString.Read(fileName),
                    (FileStreamingType)flags,
                    offset,
                    size);

                if (result.ResultType != ActionResultType.OK || result.Result == null)
                {
                    return ToHResult(result);
                }

                value = AimpBridgeHelper.GetStreamPointer(result.Result);
                return Safe.S_OK;
            });

            stream = value;
            return hr;
        }

        #endregion

        private static int ToHResult(AimpActionResult result)
        {
            return result == null ? Safe.E_FAIL : (int)result.ResultType;
        }
    }
}
