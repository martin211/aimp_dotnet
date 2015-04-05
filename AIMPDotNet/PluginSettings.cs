using System.ComponentModel;
using System.Runtime.CompilerServices;
using AIMP.SDK.Annotations;

namespace AIMP.SDK
{
    /// <summary>
    /// DotNet plugin settings.
    /// </summary>
    internal class PluginSettings : INotifyPropertyChanged
    {
        /// <summary>
        /// Gets or sets a value indicating whether this instance is debug mode.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is debug mode; otherwise, <c>false</c>.
        /// </value>
        public bool IsDebugMode { get; set; }

        /// <summary>
        /// Gets or sets the plugins collection.
        /// </summary>
        /// <value>
        /// The plugins collection.
        /// </value>
        public PluginInfoCollection PluginsCollection { get; set; }

        public event PropertyChangedEventHandler PropertyChanged;

        [NotifyPropertyChangedInvocator]
        protected virtual void OnPropertyChanged([CallerMemberName] string propertyName = null)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
    }
}