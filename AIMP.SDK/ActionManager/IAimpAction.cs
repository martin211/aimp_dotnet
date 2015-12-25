namespace AIMP.SDK.ActionManager
{
    /// <summary>
    /// Action item interface.
    /// </summary>
    public interface IAimpAction : IAimpActionEvent
    {
        /// <summary>
        /// Gets or sets the identifier.
        /// </summary>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the custom data.
        /// </summary>
        string CustomData { get; set; }

        /// <summary>
        /// Gets or sets the name.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets the name of the group.
        /// </summary>
        string GroupName { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpAction"/> is enabled.
        /// </summary>
        bool Enabled { get; set; }

        /// <summary>
        /// Gets or sets the default hot key.
        /// </summary>
        int DefaultLocalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the default global hot key.
        /// </summary>
        int DefaultGlobalHotKey { get; set; }

        /// <summary>
        /// Gets or sets the default global hot key2.
        /// </summary>
        int DefaultGlobalHotKey2 { get; set; }
    }
}