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
    /// <summary>
    /// Provide ability to get access to tag editor.
    /// </summary>
    public interface IAimpFileTagEditor
    {
        /// <summary>
        /// Gets the mixed information from all tags and returns it as a <see cref="IAimpFileInfo"/>.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        AimpActionResult GetMixedInfo(out IAimpFileInfo fileInfo);

        /// <summary>
        /// Gets the tag.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="fileTag">The file tag.</param>
        AimpActionResult GetTag(int index, out IAimpFileTag fileTag);

        /// <summary>
        /// Gets the tag count.
        /// </summary>
        int GetTagCount();

        /// <summary>
        /// Sets value to all tags.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        AimpActionResult SetToAll(IAimpFileInfo fileInfo);

        /// <summary>
        /// Saves all changes to file.
        /// </summary>
        AimpActionResult Save();
    }
}