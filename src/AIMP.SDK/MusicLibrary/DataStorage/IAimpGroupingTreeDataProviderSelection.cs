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

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    [Flags]
    public enum GroupingTreeNodeFlags
    {
        HasChildren = 1,
        Standalone = 2
    }

    public enum FieldImageIndex
    {
        Folder = 0,
        Artist = 1,
        Disk = 2,
        Note = 3,
        Star = 4,
        Calendar = 5,
        Label = 6
    }

    /// <summary>
    /// Interface provides an access to data from the <seealso cref="IAimpGroupingTreeDataProvider.GetData"/>.
    /// Interface implementation must support asynchronous access.
    /// </summary>
    public interface IAimpGroupingTreeDataProviderSelection
    {
        /// <summary>
        /// Returns text to display to end user (optionally).
        /// </summary>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        AimpActionResult<string> GetDisplayValue();

        /// <summary>
        /// Gets the tree node flags <see cref="GroupingTreeNodeFlags"/>.
        /// <note>
        /// AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN - current node has children.
        /// AIMPML_GROUPINGTREENODE_FLAG_STANDALONE <see cref="IAimpGroupingTreeSelection"/>.
        /// </note>
        /// </summary>
        GroupingTreeNodeFlags GetFlags();

        /// <summary>
        /// Return the node image <see cref="FieldImageIndex"/>.
        /// </summary>
        AimpActionResult<FieldImageIndex> GetImageIndex();

        /// <summary>
        /// Returns the value for specified field name.
        /// </summary>
        /// <param name="fieldName">THe current field name.</param>
        /// <param name="value"></param>
        AimpActionResult<string, object> GetValue();

        /// <summary>
        /// Jumps to the next record. Returns False if current node is last.
        /// </summary>
        bool NextRow();
    }
}