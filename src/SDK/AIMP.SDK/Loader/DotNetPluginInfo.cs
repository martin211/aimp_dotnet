//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections;
using System.Collections.Generic;
using AIMP.Properties;

namespace AIMP.Loader
{
    /// <summary>
    /// Plugins information collection.
    /// Implements the <see cref="AIMP.Loader.PluginInformation" />
    /// </summary>
    /// <seealso cref="AIMP.Loader.PluginInformation" />
    // TODO: replace on one instance
    public class DotNetPluginInfo : ICollection<PluginInformation>
    {
        /// <summary>
        /// The in plugins list
        /// </summary>
        private readonly List<PluginInformation> _inPluginsList;

        /// <summary>
        /// Initializes a new instance of the <see cref="DotNetPluginInfo" /> class.
        /// </summary>
        public DotNetPluginInfo()
        {
            _inPluginsList = new List<PluginInformation>();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="DotNetPluginInfo" /> class.
        /// </summary>
        /// <param name="pluginInformations">The plugin informations.</param>
        public DotNetPluginInfo(IEnumerable<PluginInformation> pluginInformations)
        {
            _inPluginsList = new List<PluginInformation>(pluginInformations);
            foreach (var item in pluginInformations)
            {
                item.PluginLoadEvent += item_PluginLoadEvent;
                item.PluginUnloadEvent += item_PluginUnloadEvent;
            }
        }

        /// <summary>
        /// Gets the <see cref="AIMP.Loader.PluginInformation" /> with the specified identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>PluginInformation.</returns>
        public PluginInformation this[int id] => _inPluginsList[id];

        /// <summary>
        /// Adds an item to the <see cref="T:System.Collections.Generic.ICollection`1" />.
        /// </summary>
        /// <param name="item">The object to add to the <see cref="T:System.Collections.Generic.ICollection`1" />.</param>
        public void Add([NotNull] PluginInformation item)
        {
            _inPluginsList.Add(item);
            item.PluginLoadEvent += item_PluginLoadEvent;
            item.PluginUnloadEvent += item_PluginUnloadEvent;
        }

        /// <summary>
        /// Removes all items from the <see cref="T:System.Collections.Generic.ICollection`1" />.
        /// </summary>
        public void Clear()
        {
            UnloadAll();
            foreach (var item in _inPluginsList)
            {
                item.PluginLoadEvent -= item_PluginLoadEvent;
                item.PluginUnloadEvent -= item_PluginUnloadEvent;
            }

            _inPluginsList.Clear();
        }

        /// <summary>
        /// Determines whether the <see cref="T:System.Collections.Generic.ICollection`1" /> contains a specific value.
        /// </summary>
        /// <param name="item">The object to locate in the <see cref="T:System.Collections.Generic.ICollection`1" />.</param>
        /// <returns>true if <paramref name="item" /> is found in the <see cref="T:System.Collections.Generic.ICollection`1" />;
        /// otherwise, false.</returns>
        public bool Contains(PluginInformation item)
        {
            return _inPluginsList.Contains(item);
        }

        /// <summary>
        /// Copies to.
        /// </summary>
        /// <param name="array">The array.</param>
        /// <param name="arrayIndex">Index of the array.</param>
        public void CopyTo(PluginInformation[] array, int arrayIndex)
        {
            _inPluginsList.CopyTo(array, arrayIndex);
        }

        /// <summary>
        /// Gets the number of elements contained in the <see cref="T:System.Collections.Generic.ICollection`1" />.
        /// </summary>
        /// <value>The count.</value>
        public int Count => _inPluginsList.Count;

        /// <summary>
        /// Gets a value indicating whether the <see cref="T:System.Collections.Generic.ICollection`1" /> is read-only.
        /// </summary>
        /// <value><c>true</c> if this instance is read only; otherwise, <c>false</c>.</value>
        public bool IsReadOnly => false;

        /// <summary>
        /// Removes the first occurrence of a specific object from the
        /// <see cref="T:System.Collections.Generic.ICollection`1" />.
        /// </summary>
        /// <param name="item">The object to remove from the <see cref="T:System.Collections.Generic.ICollection`1" />.</param>
        /// <returns>true if <paramref name="item" /> was successfully removed from the
        /// <see cref="T:System.Collections.Generic.ICollection`1" />; otherwise, false. This method also returns false if
        /// <paramref name="item" /> is not found in the original <see cref="T:System.Collections.Generic.ICollection`1" />.</returns>
        public bool Remove( [NotNull] PluginInformation item)
        {
            var res = _inPluginsList.Remove(item);
            if (res)
            {
                item.Unload();
                item.PluginLoadEvent -= item_PluginLoadEvent;
                item.PluginUnloadEvent -= item_PluginUnloadEvent;
            }

            return res;
        }

        /// <summary>
        /// Returns an enumerator that iterates through the collection.
        /// </summary>
        /// <returns>A <see cref="T:System.Collections.Generic.IEnumerator`1" /> that can be used to iterate through the
        /// collection.</returns>
        public IEnumerator<PluginInformation> GetEnumerator()
        {
            return _inPluginsList.GetEnumerator();
        }

        /// <summary>
        /// Returns an enumerator that iterates through a collection.
        /// </summary>
        /// <returns>An <see cref="T:System.Collections.IEnumerator" /> object that can be used to iterate through the collection.</returns>
        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        /// <summary>
        /// Adds the range.
        /// </summary>
        /// <param name="col">The col.</param>
        public void AddRange(IEnumerable<PluginInformation> col)
        {
            _inPluginsList.AddRange(col);
            foreach (var item in col)
            {
                item.PluginLoadEvent += item_PluginLoadEvent;
                item.PluginUnloadEvent += item_PluginUnloadEvent;
            }
        }

        /// <summary>
        /// Unloads all.
        /// </summary>
        public void UnloadAll()
        {
            foreach (var inf in _inPluginsList)
            {
                inf.Unload();
            }
        }

        /// <summary>
        /// Occurs when current plugin is loaded.
        /// </summary>
        public event PluginLoadUnloadEvent PluginLoadEvent;

        /// <summary>
        /// Occurs when current plugin is inloaded.
        /// </summary>
        public event PluginLoadUnloadEvent PluginUnloadEvent;

        /// <summary>
        /// Item_s the plugin load event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        private void item_PluginLoadEvent(PluginInformation sender)
        {
            if (PluginLoadEvent != null)
            {
                PluginLoadEvent(sender);
            }
        }

        /// <summary>
        /// Item_s the plugin unload event.
        /// </summary>
        /// <param name="sender">The sender.</param>
        private void item_PluginUnloadEvent(PluginInformation sender)
        {
            if (PluginUnloadEvent != null)
            {
                PluginUnloadEvent(sender);
            }
        }
    }
}
