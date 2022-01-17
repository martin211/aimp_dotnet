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

namespace AIMP.SDK.Actions
{
    /// <summary>
    /// Main feature of Action is an ability to display it in hotkey list, and provide an ability to customize it hotkey.
    /// Implements the <see cref="IAimpActionEvent" />
    /// Implements the <see cref="AIMP.SDK.IAimpObject" />
    /// </summary>
    /// <seealso cref="IAimpActionEvent" />
    /// <seealso cref="AIMP.SDK.IAimpObject" />
    public interface IAimpAction : IAimpActionEvent, IAimpObject
    {
        /// <summary>
        /// Gets or sets the unique action identity, must be unique for all plugins.
        /// </summary>
        /// <value>The identifier.</value>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the custom data.
        /// </summary>
        /// <value>The custom data.</value>
        string CustomData { get; set; }

        /// <summary>
        /// Gets or sets the command name, value is displaying in the hotkey list.
        /// </summary>
        /// <value>The name.</value>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets the group name. Optional, can be undefined.
        /// </summary>
        /// <value>The name of the group.</value>
        string GroupName { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpAction" /> is enabled.
        /// </summary>
        /// <value><c>true</c> if enabled; otherwise, <c>false</c>.</value>
        bool Enabled { get; set; }

        /// <summary>
        /// Gets or sets the default hot key. Can be 0.
        /// </summary>
        /// <value>The default local hot key.</value>
        int DefaultLocalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the default global hot key. Can be 0.
        /// </summary>
        /// <value>The default global hot key.</value>
        int DefaultGlobalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the alternative global hot key. Can be 0.
        /// </summary>
        /// <value>The alternative global hot key.</value>
        int AlternativeGlobalHotKey { get; set; }
    }
}
