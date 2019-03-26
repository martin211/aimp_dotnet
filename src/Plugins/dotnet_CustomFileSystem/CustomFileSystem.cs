// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2019 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------
using System.Collections.Generic;
using System.Windows;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Commands;
using AIMP.SDK.FileManager.Extensions;
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
        private const string MyScheme = "mymusic";
        public static string MySchemePrefix = MyScheme + @":\\";

        private readonly IAimpPlayer _aimpPlayer;

        public CustomFileSystem(IAimpPlayer aimpPlayer)
        {
            _aimpPlayer = aimpPlayer;
        }

        public string Schema => MyScheme;

        public bool ReadOnly => true;

        public AimpActionResult CopyToClipboard(List<string> files)
        {
            Clipboard.SetText(string.Join(",", files));
            return AimpActionResult.OK;
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

        public IAimpStream CreateStream(string fileName)
        {
            var result = GetCommand(FileCommandType.Delete, fileName, out IAimpFileSystemCommandDropSource cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                return cmd.CreateStream(GetFile(fileName));
            }

            return null;
        }

        public AimpActionResult GetFileAttrs(string fileName, out AimpFileAttributes attr)
        {
            attr = new AimpFileAttributes();
            var result = GetCommand(FileCommandType.FileInfo, fileName, out IAimpFileSystemCommandFileInfo cmd);

            if (result == AimpActionResult.OK && cmd != null)
            {
                if (cmd.GetFileAttrs(GetFile(fileName), out var at) == AimpActionResult.OK)
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
                result = cmd.GetFileSize(GetFile(fileName), out size);
            }

            return result;
        }

        public AimpActionResult IsFileExists(string fileName)
        {
            var result = GetCommand(FileCommandType.FileInfo, fileName, out IAimpFileSystemCommandFileInfo cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = cmd.IsFileExists(GetFile(fileName));
            }

            return result;
        }

        AimpActionResult IAimpFileSystemCommandOpenFileFolder.CanProcess(string fileName)
        {
            var result = GetCommand(FileCommandType.OpenFileFolder, fileName, out IAimpFileSystemCommandOpenFileFolder cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = cmd.CanProcess(GetFile(fileName));
            }

            return result;
        }

        AimpActionResult IAimpFileSystemCommandOpenFileFolder.Process(string fileName)
        {
            var result = GetCommand(FileCommandType.OpenFileFolder, fileName, out IAimpFileSystemCommandOpenFileFolder cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                result = cmd.Process(GetFile(fileName));
            }

            return result;
        }

        public IAimpStream CreateStream(string fileName, FileStreamingType flags, long offset, long size)
        {
            var result = GetCommand(FileCommandType.Delete, fileName, out IAimpFileSystemCommandStreaming cmd);
            if (result == AimpActionResult.OK && cmd != null)
            {
                return cmd.CreateStream(GetFile(fileName), flags, offset, size);
            }

            return null;
        }

        private AimpActionResult GetCommand<TCommand>(FileCommandType commandType, string file, out TCommand command)
        {
            var res = _aimpPlayer.ServiceFileSystems.Get(commandType, GetFile(file), out var cmd);
            command = (TCommand)cmd;
            return res;
        }

        private string GetFile(string file)
        {
            return file.Replace(MySchemePrefix, string.Empty);
        }
    }
}