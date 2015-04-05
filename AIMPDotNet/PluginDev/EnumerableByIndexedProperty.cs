using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace dotNetInteropPlugin.PluginDev
{
    internal class EnumerableByIndexedProperty: IEnumerable<IMAIMPFileInfoReadOnly>
    {

        public EnumerableByIndexedProperty(MAIMPDisconnectedPlaylist info)
        {
            inInfo = info;
        }
        private MAIMPDisconnectedPlaylist inInfo = null;


        public IEnumerator<IMAIMPFileInfoReadOnly> GetEnumerator()
        {
            for (int i = 0; i < inInfo.Count; i++)
                yield return inInfo[i];
        }

        System.Collections.IEnumerator System.Collections.IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }
    }
}
