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
using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;

namespace AIMP.DotNet.MusicLibrary
{
    public class DemoExtensionFileSystem : IAimpExtensionFileSystem, IAimpExtension//, IAimpFileSystemCommandOpenFileFolder
    {
        public string Schema => "myschema";

        public bool ReadOnly => false;

        public AimpActionResult CreateStream(string file, out IAimpStream stream)
        {
            stream = null;
            return AimpActionResult.NotImplemented;
        }

        public AimpActionResult CanProcess(string file)
        {
            return AimpActionResult.OK;
        }

        public AimpActionResult Process(string file)
        {
            return AimpActionResult.OK;
        }
    }
}
