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

using AIMP.SDK;
using AIMP.SDK.MusicLibrary.DataStorage;

namespace AIMP.DotNet.MusicLibrary.ExplorerMusicProvider
{
    public class CustomAimpGroupingTreeDataProviderSelection : IAimpGroupingTreeDataProviderSelection
    {
        public AimpActionResult<string> GetDisplayValue()
        {
            return new AimpActionResult<string>(ActionResultType.OK, "Test value");
        }

        public GroupingTreeNodeFlags GetFlags()
        {
            return GroupingTreeNodeFlags.HasChildren;
        }

        public AimpActionResult<FieldImageIndex> GetImageIndex()
        {
            return new AimpActionResult<FieldImageIndex>(ActionResultType.OK, FieldImageIndex.Folder);
        }

        public AimpActionResult<string, object> GetValue()
        {
            return new AimpActionResult<string, object>(ActionResultType.OK, "fn", 1);
        }

        public bool NextRow()
        {
            return true;
        }
    }
}
