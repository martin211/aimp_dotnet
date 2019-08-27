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
using AIMP.SDK.FileManager;

namespace AIMP.SDK.TagEditor
{
    public interface IAimpFileTag : IAimpFileInfo
    {
        TagType TagId { get; set; }

        bool DeleteOnSaving { get; set; }
    }
}