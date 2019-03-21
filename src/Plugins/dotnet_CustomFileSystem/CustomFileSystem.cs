using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Windows;
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
        IAimpFileSystemCommandCopyToClipboard,
        IAimpFileSystemCommandDelete,
        IAimpFileSystemCommandDropSource,
        IAimpFileSystemCommandOpenFileFolder,
        IAimpFileSystemCommandFileInfo,
        IAimpFileSystemCommandStreaming
    {
        private const string sMyScheme = "mymusic";
        public const string sMySchemePrefix = sMyScheme + @":\\";

        private readonly IAimpPlayer _aimpPlayer;

        public CustomFileSystem(IAimpPlayer aimpPlayer)
        {
            _aimpPlayer = aimpPlayer;
        }

        public string Schema => sMyScheme;

        public bool ReadOnly => true;

        public AimpActionResult GetFileAttrs(string fileName, out AimpFileAttributes attr)
        {
            attr = new AimpFileAttributes();
            var result = GetCommand(FileCommandType.FileInfo, fileName, out IAimpFileSystemCommandFileInfo cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                var f = fileName.Replace(sMySchemePrefix, string.Empty);
                if (cmd.GetFileAttrs(f, out var at) == AimpActionResult.OK)
                {
                    attr = at;
                }
            }

            return result;
        }

        public AimpActionResult GetFileSize(string fileName, out long size)
        {
            size = 0;
            var result = GetCommand(FileCommandType.FileInfo, fileName, out IAimpFileSystemCommandFileInfo cmd);

            if (result == AimpActionResult.OK && cmd != null)
            {
                var f = fileName.Replace(sMySchemePrefix, string.Empty);
                result = cmd.GetFileSize(f, out size);
            }

            return result;
        }

        public AimpActionResult IsFileExists(string fileName)
        {
            var result = GetCommand(FileCommandType.FileInfo, fileName, out IAimpFileSystemCommandFileInfo cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                var f = fileName.Replace(sMySchemePrefix, string.Empty);
                result = cmd.IsFileExists(f);
            }

            return result;
        }

        AimpActionResult IAimpFileSystemCommandDelete.CanProcess(string fileName)
        {
            var result = GetCommand(FileCommandType.Delete, fileName, out IAimpFileSystemCommandDelete cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = cmd.CanProcess(fileName);
            }

            return result;
        }

        AimpActionResult IAimpFileSystemCommandDelete.Process(string fileName)
        {
            var result = GetCommand(FileCommandType.Delete, fileName, out IAimpFileSystemCommandDelete cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = cmd.Process(fileName);
            }

            return result;
        }

        public IAimpStream CreateStream(string fileName, FileStreamingType flags, long offset, long size)
        {
            var file = fileName.Replace(sMySchemePrefix, string.Empty);

            var result = _aimpPlayer.ServiceFileSystems.Get(FileCommandType.Streaming, file, out var cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                return (cmd as IAimpFileSystemCommandStreaming).CreateStream(file, flags, offset, size);
            }

            if (!File.Exists(file))
            {
                return null;
            }

            if (flags.HasFlag(FileStreamingType.AIMP_SERVICE_FILESTREAMING_FLAG_READ))
            {
                using (var fs = new FileStream(file, FileMode.Open))
                {
                    offset = offset == -1 ? 0 : offset;
                    size = size == -1 ? fs.Length : size;
                    var stream = _aimpPlayer.Core.CreateStream();
                    byte[] buffer = new byte[size];
                    fs.Read(buffer, (int) offset, buffer.Length);
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

        public IAimpStream CreateStream(string fileName)
        {
            var file = fileName.Replace(sMySchemePrefix, string.Empty);

            var result = _aimpPlayer.ServiceFileSystems.Get(FileCommandType.DropSource, file, out var cmd);

            if (result == AimpActionResult.OK && cmd != null)
            {
                return (cmd as IAimpFileSystemCommandDropSource).CreateStream(file);
            }

            return null;
        }

        AimpActionResult IAimpFileSystemCommandOpenFileFolder.CanProcess(string fileName)
        {
            var file = fileName.Replace(@"mymusic:\\", string.Empty);
            var result = _aimpPlayer.ServiceFileSystems.Get(FileCommandType.OpenFileFolder, file, out var cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = (cmd as IAimpFileSystemCommandOpenFileFolder).CanProcess(file);
            }

            return result;
        }

        AimpActionResult IAimpFileSystemCommandOpenFileFolder.Process(string fileName)
        {
            var file = fileName.Replace(@"mymusic:\\", string.Empty);
            var result = _aimpPlayer.ServiceFileSystems.Get(FileCommandType.OpenFileFolder, file, out var cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = (cmd as IAimpFileSystemCommandOpenFileFolder).Process(file);
            }

            return result;
        }

        public AimpActionResult CopyToClipboard(List<string> files)
        {
            Clipboard.SetText(string.Join(",", files));
            return AimpActionResult.OK;
        }

        private AimpActionResult GetCommandForDefaultFileSystem<TCommand>(FileCommandType commandType, out TCommand command)
            where TCommand : IAimpFileSystemCommand
        {
            var res = _aimpPlayer.ServiceFileSystems.GetDefault(commandType, out var cmd);
            command = (TCommand)cmd;
            return res;
        }

        private AimpActionResult GetCommand<TCommand>(FileCommandType commandType, string file, out TCommand command)
        {
            var f = file.Replace(sMySchemePrefix, string.Empty);
            var res = _aimpPlayer.ServiceFileSystems.Get(commandType, f, out var cmd);
            command = (TCommand)cmd;
            return res;
        }
    }
}