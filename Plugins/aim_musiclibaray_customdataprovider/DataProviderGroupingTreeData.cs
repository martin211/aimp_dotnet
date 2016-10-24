using System.Collections.Generic;

namespace AIMP.CustomDataProvider
{
    public class DataProviderGroupingTreeNode
    {
        public string DiaplyValue { get; set; }

        public bool HasChildren { get; set; }

        public int ImageIndex { get; set; }

        public bool Standalone { get; set; }

        public string Value { get; set; }
    }

    public class DataProviderGroupingTreeData : List<DataProviderGroupingTreeNode>
    {
        
    }
}