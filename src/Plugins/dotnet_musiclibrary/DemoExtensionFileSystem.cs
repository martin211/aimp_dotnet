// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using AIMP.SDK;
using AIMP.SDK.FileManager.Extensions;
using AIMP.SDK.Objects;

namespace AIMP.DotNet.MusicLibrary
{
    public class
        DemoExtensionFileSystem : IAimpExtensionFileSystem, IAimpExtension //, IAimpFileSystemCommandOpenFileFolder
    {
        public string Schema => "myschema";

        public bool ReadOnly => false;

        public ActionResultType CreateStream(string file, out IAimpStream stream)
        {
            stream = null;
            return ActionResultType.NotImplemented;
        }

        public ActionResultType CanProcess(string file)
        {
            return ActionResultType.OK;
        }

        public ActionResultType Process(string file)
        {
            return ActionResultType.OK;
        }
    }
}
