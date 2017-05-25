// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

namespace AIMP.SDK.ActionManager
{
    /// <summary>
    /// Main feature of Action is an ability to display it in hotkey list, and provide an ability to customize it hotkey.
    /// </summary>
    public interface IAimpAction : IAimpActionEvent
    {
        /// <summary>
        /// Gets or sets the unique action identificator, must be unique for all plugins.
        /// </summary>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the custom data.
        /// </summary>
        string CustomData { get; set; }

        /// <summary>
        /// Gets or sets the command name, value is displaying in the hotkey list.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets the group name. Optional, can be undefined.
        /// </summary>
        string GroupName { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpAction"/> is enabled.
        /// </summary>
        bool Enabled { get; set; }

        /// <summary>
        /// Gets or sets the default hot key. Can be 0.
        /// </summary>
        int DefaultLocalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the default global hot key. Can be 0.
        /// </summary>
        int DefaultGlobalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the alternative global hot key. Can be 0.
        /// </summary>
        int AlternativeGlobalHotKey { get; set; }
    }
}