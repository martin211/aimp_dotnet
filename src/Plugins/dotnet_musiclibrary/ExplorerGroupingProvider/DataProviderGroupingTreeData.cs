﻿using System;
using System.Collections.Generic;

namespace AIMP.DotNet.MusicLibrary.ExplorerGroupingProvider
{
    public class DataProviderGroupingTreeNode
    {
        public string DisplayValue { get; set; }

        public bool HasChildren { get; set; }

        public int ImageIndex { get; set; }

        public bool Standalone { get; set; }

        public object Value { get; set; }
    }


    public class DataProviderGroupingTreeData : List<DataProviderGroupingTreeNode>
    {
        public double ReadDouble(int fieldIndex)
        {
            return 0;
        }

        public int ReadInt(int fieldIndex)
        {
            return 0;
        }

        public string ReadString(int fieldIndex)
        {
            return String.Empty;
        }
    }
}