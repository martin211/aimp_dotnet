//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Enum GroupingTreeNodeFlags
    /// </summary>
    [Flags]
    public enum GroupingTreeNodeFlags
    {
        /// <summary>
        /// The has children
        /// </summary>
        HasChildren = 1,

        /// <summary>
        /// The standalone
        /// </summary>
        Standalone = 2
    }

    /// <summary>
    /// Enum FieldImageIndex
    /// </summary>
    public enum FieldImageIndex
    {
        /// <summary>
        /// The folder
        /// </summary>
        Folder = 0,

        /// <summary>
        /// The artist
        /// </summary>
        Artist = 1,

        /// <summary>
        /// The disk
        /// </summary>
        Disk = 2,

        /// <summary>
        /// The note
        /// </summary>
        Note = 3,

        /// <summary>
        /// The star
        /// </summary>
        Star = 4,

        /// <summary>
        /// The calendar
        /// </summary>
        Calendar = 5,

        /// <summary>
        /// The label
        /// </summary>
        Label = 6
    }

    /// <summary>
    /// Interface provides an access to data from the <seealso cref="IAimpGroupingTreeDataProvider.GetData" />.
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpGroupingTreeDataProviderSelection
    {
        /// <summary>
        /// Returns text to display to end user (optionally).
        /// </summary>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> GetDisplayValue();

        /// <summary>
        /// Gets the tree node flags <see cref="GroupingTreeNodeFlags" />.
        /// <note>
        /// AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN - current node has children.
        /// AIMPML_GROUPINGTREENODE_FLAG_STANDALONE <see cref="IAimpGroupingTreeSelection" />.
        /// </note>
        /// </summary>
        /// <returns>GroupingTreeNodeFlags.</returns>
        GroupingTreeNodeFlags GetFlags();

        /// <summary>
        /// Return the node image <see cref="FieldImageIndex" />.
        /// </summary>
        /// <returns>AimpActionResult&lt;FieldImageIndex&gt;.</returns>
        AimpActionResult<FieldImageIndex> GetImageIndex();

        /// <summary>
        /// Returns the value for specified field name.
        /// </summary>
        /// <returns>AimpActionResult&lt;System.String, System.Object&gt;.</returns>
        AimpActionResult<string, object> GetValue();

        /// <summary>
        /// Jumps to the next record. Returns False if current node is last.
        /// </summary>
        /// <returns><c>true</c> if XXXX, <c>false</c> otherwise.</returns>
        bool NextRecord();
    }
}
