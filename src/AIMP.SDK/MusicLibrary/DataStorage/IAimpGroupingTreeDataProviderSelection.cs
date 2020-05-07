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
using System;

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    [Flags]
    public enum GroupingTreeNodeFlags
    {
        AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN = 1,
        AIMPML_GROUPINGTREENODE_FLAG_STANDALONE = 2
    }

    public enum FieldImageIndex
    {
        AIMPML_FIELDIMAGE_FOLDER = 0,
        AIMPML_FIELDIMAGE_ARTIST = 1,
        AIMPML_FIELDIMAGE_DISK = 2,
        AIMPML_FIELDIMAGE_NOTE = 3,
        AIMPML_FIELDIMAGE_STAR = 4,
        AIMPML_FIELDIMAGE_CALENDAR = 5,
        AIMPML_FIELDIMAGE_LABEL = 6
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
        /// <param name="displayValue">The display value.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetDisplayValue(out string displayValue);

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
        /// <param name="imageIndex">Out. The image index <see cref="FieldImageIndex"/>.</param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetImageIndex(out FieldImageIndex imageIndex);

        /// <summary>
        /// Returns the value for specified field name.
        /// </summary>
        /// <param name="fieldName">THe current field name.</param>
        /// <param name="value"></param>
        /// <returns>Operation result <seealso cref="ActionResultType"/></returns>
        ActionResultType GetValue(out string fieldName, out object value);

        /// <summary>
        /// Jumps to the next record. Returns False if current node is last.
        /// </summary>
        bool NextRow();
    }
}