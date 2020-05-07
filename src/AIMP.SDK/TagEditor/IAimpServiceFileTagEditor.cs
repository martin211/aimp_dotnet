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
    public enum TagType
    {
        Custom = 0,
        ApeV2 = 1,
        ID3v1 = 2,
        ID3v2 = 3,
        Vorbis = 4,
        M4A = 5,
        WMA = 6
    }

    /// <summary>
    /// Provide possibility to access an file tag editor service.
    /// </summary>
    public interface IAimpServiceFileTagEditor : IAimpService
    {
        ActionResultType EditFile(string filePath, out IAimpFileTagEditor editor);

        ActionResultType EditFile(IAimpStream fileStream, out IAimpFileTagEditor editor);

        ActionResultType EditTag(string filePath, TagType tag, out IAimpFileInfo fileInfo);

        ActionResultType EditTag(IAimpStream fileStream, TagType tag, out IAimpFileInfo fileInfo);
    }
}