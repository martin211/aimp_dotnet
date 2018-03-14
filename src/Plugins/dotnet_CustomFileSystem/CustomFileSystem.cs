using System;
using System.Collections.Generic;
using System.IO;
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

        public AimpActionResult GetFileAttrs(string file, out AimpFileAttributes attr)
        {
            System.Diagnostics.Debugger.Launch();
            attr = new AimpFileAttributes();
            IAimpFileSystemCommandFileInfo command;
            //if (GetCommandForDefaultFileSystem<IAimpFileSystemCommandFileInfo>(out command) == AimpActionResult.Ok)
            //{
            //    AimpFileAttributes at;
            //    if (command.GetFileAttrs(file, out at) == AimpActionResult.Ok)
            //    {
            //        attr = at;
            //    }
            //}
            attr.Attributes = FileAttributes.Normal;
            attr.TimeCreation = DateTime.Now;
            attr.TimeLastAccess = DateTime.Now;
            attr.TimeLastWrite = DateTime.Now;

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

        public AimpActionResult CanProcess(string file)
        {
            throw new NotImplementedException();
        }

        public AimpActionResult Process(string file)
        {
            throw new NotImplementedException();
        }

        public AimpActionResult CanDelete(string fileName)
        {
            throw new NotImplementedException();
        }

        public AimpActionResult CreateStream(string file, IAimpStream stream)
        {
            throw new NotImplementedException();
        }

        public AimpActionResult CreateStream(string fileName, FileStreamingType flags, long offset, long size, out IAimpStream stream)
        {
            throw new NotImplementedException();
        }
    }
}