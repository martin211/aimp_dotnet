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

namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Interface provides an access to selected nodes in grouping tree.
    /// <note>
    /// First element in the Selection is focused node. If current node does not have the
    /// AIMPML_GROUPINGTREENODE_FLAG_STANDALONE flag - the parent node will be added to Selection.
    /// Algorithm running until root or node with the AIMPML_GROUPINGTREENODE_FLAG_STANDALONE flag.
    /// </note>
    /// </summary>
    public interface IAimpGroupingTreeSelection
    {
        /// <summary>
        /// Gets the count.
        /// </summary>
        /// <returns>System.Int32.</returns>
        int GetCount();

        /// <summary>
        /// Gets the value.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <returns>AimpActionResult&lt;System.String, System.Object&gt;.</returns>
        AimpActionResult<string, object> GetValue(int index);
    }
}