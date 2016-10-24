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
    /// </summary>
    public interface IAimpGroupingTreeDataProviderSelection
    {
        /// <summary>
        /// Returns text to display to end user (optionally).
        /// </summary>
        /// <param name="displayValue">The display value.</param>
        /// <returns></returns>
        AimpActionResult GetDisplayValue(out string displayValue);

        /// <summary>
        /// Gets the tree node flags.
        /// </summary>
        GroupingTreeNodeFlags GetFlags();

        AimpActionResult GetImageIndex(out FieldImageIndex imageIndex);

        AimpActionResult GetValue(out string fieldName, out object value);

        /// <summary>
        /// Jumps to the next record. Returns False if current node is last.
        /// </summary>
        bool NextRow();
    }
}