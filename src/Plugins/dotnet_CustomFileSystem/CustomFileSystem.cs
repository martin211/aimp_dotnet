using System;
using System.Collections.Generic;
using System.IO;
using System.Runtime.InteropServices;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Commands;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;
using AIMP.SDK.Player;

namespace AIMP.SDK.CustomFileSystem
{
    public class CustomFileSystem :
        IAimpExtension,
        IAimpExtensionFileSystem,
        IAimpFileSystemCommandDropSource,
        IAimpFileSystemCommandOpenFileFolder
    {
        private const string sMyScheme = "mymusic";
        public const string sMySchemePrefix = sMyScheme + @":\\";

        private readonly IAimpPlayer _aimpPlayer;

        public CustomFileSystem(IAimpPlayer aimpPlayer)
        {
            _aimpPlayer = aimpPlayer;
        }

        public string Schema
        {
            get { return sMyScheme; }
        }

        public bool ReadOnly
        {
            get { return true; }
        }

        public AimpActionResult CopyToClipboard(IList<string> files)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileAttrs(IAimpString fileName, out AimpFileAttributes attr)
        {
            System.Diagnostics.Debugger.Launch();
            attr = new AimpFileAttributes();

            //var f = (IAimpString)Marshal.GetObjectForIUnknown(fileName);
            //var a = f.GetLength();
            //var l = f.GetData();
            var file = "";

            if (File.Exists(file))
            {
                attr.Attributes = FileAttributes.Normal;
                attr.TimeCreation = File.GetCreationTime(file);
                attr.TimeLastAccess = File.GetLastAccessTime(file);
                attr.TimeLastWrite = File.GetLastWriteTime(file);

                return AimpActionResult.Ok;
            }

            IAimpFileSystemCommandFileInfo command;
            if (GetCommandForDefaultFileSystem<IAimpFileSystemCommandFileInfo>(out command) == AimpActionResult.Ok)
            {
            //    AimpFileAttributes at;
            //    if (command.GetFileAttrs(file, out at) == AimpActionResult.Ok)
            //    {
            //        attr = at;
            //    }
            }

            return AimpActionResult.Fail;
        }

        public AimpActionResult GetFileSize(IAimpString fileName, out long size)
        {
            size = 0;
            var file = GetFile(fileName.GetData());

            if (File.Exists(file))
            {
                var fi = new FileInfo(file);
                size = fi.Length;
                return AimpActionResult.Ok;
            }

            return AimpActionResult.Fail;
        }

        public AimpActionResult IsFileExists(IAimpString fileName)
        {
            var file = GetFile(fileName.GetData());
            return File.Exists(file) ? AimpActionResult.Ok : AimpActionResult.Fail;
        }

        private AimpActionResult GetCommandForDefaultFileSystem<TCommand>(out TCommand command) 
            where TCommand : IAimpFileSystemCommand
        {
            IAimpFileSystemCommand cmd;
            var res = _aimpPlayer.ServiceFileSystems.GetDefault(out cmd);
            command = (TCommand)cmd;
            return res;
        }

        public AimpActionResult CanProcess(string fileName)
        {
            var file = GetFile(fileName);
            return File.Exists(file) ? AimpActionResult.Ok : AimpActionResult.Fail;
        }

        public AimpActionResult Process(string fileName)
        {
            var file = GetFile(fileName);
            return File.Exists(file) ? AimpActionResult.Ok : AimpActionResult.Fail;
        }

        public AimpActionResult CanDelete(string fileName)
        {
            var file = GetFile(fileName);
            return File.Exists(file) ? AimpActionResult.Ok : AimpActionResult.Fail;
        }

        public IAimpStream CreateStream(string fileName, FileStreamingType flags, long offset, long size)
        {
            var file = fileName.Replace(sMySchemePrefix, string.Empty);

            if (!File.Exists(file))
            {
                return null;
            }

            if (flags.HasFlag(FileStreamingType.AIMP_SERVICE_FILESTREAMING_FLAG_READ))
            {
                using (var fs = new FileStream(file, FileMode.Open))
                {
                    size = size == -1 ? fs.Length : size;
                    var stream = _aimpPlayer.Core.CreateStream();
                    byte[] buffer = new byte[size];
                    fs.Read(buffer, (int)offset, buffer.Length);
                    stream.Write(buffer, buffer.Length, out var written);
                    return stream;
                }
            }

            return null;
        }

        public string GetFile(string file)
        {
            return file.Replace(sMySchemePrefix, string.Empty);
        }

        public IAimpStream CreateStream(IAimpString fileName)
        {
            //var stringObject = AimpObjectHelper.GetObject<IAimpString>(fileNameHeader);
            //if (stringObject != null)
            //{
                var file = fileName.GetData().Replace(sMySchemePrefix, string.Empty);

                if (File.Exists(file))
                {
                    using (var fs = new FileStream(file, FileMode.Open))
                    {
                        var stream = _aimpPlayer.Core.CreateStream();
                        byte[] buffer = new byte[file.Length];
                        fs.Read(buffer, 0, buffer.Length);
                        stream.Write(buffer, buffer.Length, out var written);
                        return stream;
                }
                }
            //}

            return null;
        }
    }
}