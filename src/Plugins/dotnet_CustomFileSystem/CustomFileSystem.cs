using System.Collections.Generic;
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
        IAimpFileSystemCommandFileInfo
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
            get { return false; }
        }

        public AimpActionResult CopyToClipboard(IList<string> files)
        {
            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileAttrs(string file, out AimpFileAttributes attr)
        {
            System.Diagnostics.Debugger.Launch();
            attr = new AimpFileAttributes();
            IAimpFileSystemCommandFileInfo command;
            if (GetCommandForDefaultFileSystem<IAimpFileSystemCommandFileInfo>(out command) == AimpActionResult.Ok)
            {
                AimpFileAttributes at;
                if (command.GetFileAttrs(file, out at) == AimpActionResult.Ok)
                {
                    attr = at;
                }
            }

            return AimpActionResult.Ok;
        }

        public AimpActionResult GetFileSize(string file, out long size)
        {
            size = 0;
            return AimpActionResult.Ok;
        }

        public AimpActionResult IsFileExists(string file)
        {
            return AimpActionResult.Ok;
        }

        private AimpActionResult GetCommandForDefaultFileSystem<TCommand>(out TCommand command) 
            where TCommand : IAimpFileSystemCommand
        {
            IAimpFileSystemCommand cmd;
            var res = _aimpPlayer.ServiceFileSystems.GetDefault(out cmd);
            command = (TCommand)cmd;
            return res;
        }
    }
}