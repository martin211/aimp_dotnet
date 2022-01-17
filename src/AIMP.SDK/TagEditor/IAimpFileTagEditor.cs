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

using System;
using AIMP.SDK.FileManager;
using AIMP.SDK.FileManager.Primitives;

namespace AIMP.SDK.TagEditor
{
    /// <summary>
    /// Provide ability to get access to tag editor.
    /// </summary>
    public interface IAimpFileTagEditor : IDisposable
    {
        /// <summary>
        /// Gets the mixed information from all tags and returns it as a <see cref="IAimpFileInfo" />.
        /// </summary>
        /// <returns>AimpActionResult&lt;IAimpFileInfo&gt;.</returns>
        AimpActionResult<IAimpFileInfo> GetMixedInfo();

        /// <summary>
        /// Gets the tag.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;IAimpFileTag&gt;.</returns>
        AimpActionResult<IAimpFileTag> GetTag(int index);

        /// <summary>
        /// Gets the tag count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetTagCount();

        /// <summary>
        /// Sets value to all tags.
        /// </summary>
        /// <param name="fileInfo">The file information.</param>
        /// <returns>ActionResultType.</returns>
        AimpActionResult SetToAll(IAimpFileInfo fileInfo);

        /// <summary>
        /// Saves all changes to file.
        /// </summary>
        /// <returns>ActionResultType.</returns>
        AimpActionResult Save();
    }
}
