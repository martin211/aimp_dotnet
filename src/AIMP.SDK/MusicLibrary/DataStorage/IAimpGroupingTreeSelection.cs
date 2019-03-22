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
namespace AIMP.SDK.MusicLibrary.DataStorage
{
    /// <summary>
    /// Interface provides an access to selected nodes in grouping tree.
    /// <note>
    /// First element in the Selection is focused node. If current node does not have the AIMPML_GROUPINGTREENODE_FLAG_STANDALONE flag - the parent node will be added to Selection. 
    /// Algorithm running until root or node with the AIMPML_GROUPINGTREENODE_FLAG_STANDALONE flag.
    /// </note>
    /// </summary>
    public interface IAimpGroupingTreeSelection
    {
        int GetCount();

        AimpActionResult GetValue(int index, out string fieldName, out object value);
    }
}