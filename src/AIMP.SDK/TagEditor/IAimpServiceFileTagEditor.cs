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

using AIMP.SDK.FileManager;

namespace AIMP.SDK.TagEditor
{
    /// <summary>
    /// Enum TagType
    /// </summary>
    public enum TagType
    {
        /// <summary>
        /// The custom
        /// </summary>
        Custom = 0,
        /// <summary>
        /// The ape v2
        /// </summary>
        ApeV2 = 1,
        /// <summary>
        /// The i D3V1
        /// </summary>
        ID3v1 = 2,
        /// <summary>
        /// The i D3V2
        /// </summary>
        ID3v2 = 3,
        /// <summary>
        /// The vorbis
        /// </summary>
        Vorbis = 4,
        /// <summary>
        /// The m4 a
        /// </summary>
        M4A = 5,
        /// <summary>
        /// The wma
        /// </summary>
        WMA = 6
    }

    /// <summary>
    /// Provide possibility to access an file tag editor service.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceFileTagEditor : IAimpService
    {
        /// <summary>
        /// Edits the file.
        /// </summary>
        /// <param name="filePath">The file path.</param>
        /// <param name="editor">The editor.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType EditFile(string filePath, out IAimpFileTagEditor editor);

        /// <summary>
        /// Edits the file.
        /// </summary>
        /// <param name="fileStream">The file stream.</param>
        /// <param name="editor">The editor.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType EditFile(IAimpStream fileStream, out IAimpFileTagEditor editor);

        /// <summary>
        /// Edits the tag.
        /// </summary>
        /// <param name="filePath">The file path.</param>
        /// <param name="tag">The tag.</param>
        /// <param name="fileInfo">The file information.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType EditTag(string filePath, TagType tag, out IAimpFileInfo fileInfo);

        /// <summary>
        /// Edits the tag.
        /// </summary>
        /// <param name="fileStream">The file stream.</param>
        /// <param name="tag">The tag.</param>
        /// <param name="fileInfo">The file information.</param>
        /// <returns>ActionResultType.</returns>
        ActionResultType EditTag(IAimpStream fileStream, TagType tag, out IAimpFileInfo fileInfo);
    }
}