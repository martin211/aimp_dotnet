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
        public ActionResultType GetDisplayValue(out string displayValue)
        {
            displayValue = "Test value";
            return ActionResultType.OK;
        }

        public GroupingTreeNodeFlags GetFlags()
        {
            return GroupingTreeNodeFlags.AIMPML_GROUPINGTREENODE_FLAG_HASCHILDREN;
        }

        public ActionResultType GetImageIndex(out FieldImageIndex imageIndex)
        {
            imageIndex = FieldImageIndex.AIMPML_FIELDIMAGE_FOLDER;
            return ActionResultType.OK;
        }

        public ActionResultType GetValue(out string fieldName, out object value)
        {
            fieldName = "fn";
            value = 1;

            return ActionResultType.OK;
        }

        public bool NextRow()
        {
            return true;
        }
    }
}