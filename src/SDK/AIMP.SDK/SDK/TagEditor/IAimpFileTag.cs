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

using AIMP.SDK.FileManager.Objects;

namespace AIMP.SDK.TagEditor
{
    /// <summary>
    /// Interface IAimpFileTag
    /// Implements the <see cref="IAimpFileInfo" />
    /// </summary>
    /// <seealso cref="IAimpFileInfo" />
    public interface IAimpFileTag : IAimpFileInfo
    {
        /// <summary>
        /// Gets or sets the tag identifier.
        /// </summary>
        /// <value>The tag identifier.</value>
        TagType TagId { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [delete on saving].
        /// </summary>
        /// <value><c>true</c> if [delete on saving]; otherwise, <c>false</c>.</value>
        bool DeleteOnSaving { get; set; }
    }
}
