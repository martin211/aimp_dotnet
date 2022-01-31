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

using System;
using System.Drawing;
using AIMP.SDK.Actions;
using AIMP.SDK.Actions.Objects;

namespace AIMP.SDK.MenuManager.Objects
{
    /// <summary>
    /// Menu item style.
    /// </summary>
    public enum MenuItemStyle
    {
        /// <summary>
        /// The normal menu item.
        /// </summary>
        Normal,

        /// <summary>
        /// The CheckBox menu item.
        /// </summary>
        CheckBox,

        /// <summary>
        /// The radio box menu item.
        /// </summary>
        RadioBox
    }

    /// <summary>
    /// AIMP menu item interface.
    /// Implements the <see cref="IAimpActionEvent" />
    /// Implements the <see cref="AIMP.SDK.IAimpObject" />
    /// </summary>
    /// <seealso cref="IAimpActionEvent" />
    /// <seealso cref="AIMP.SDK.IAimpObject" />
    public interface IAimpMenuItem : IAimpActionEvent, IAimpObject
    {
        /// <summary>
        /// This is a user data parameter.
        /// It allow you to bind custom data to the interface.
        /// </summary>
        /// <value>The custom.</value>
        string Custom { get; set; }

        /// <summary>
        /// Provides an ability to set the <see cref="IAimpAction" /> for menu item.
        /// Menu item will inherits the Name, Enabled, OnExecute event from the action.
        /// </summary>
        /// <value>The action.</value>
        IAimpAction Action { get; set; }

        /// <summary>
        /// Gets or sets the identifier.
        /// Must be unique for all plugins.
        /// </summary>
        /// <value>The identifier.</value>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the menu item display name.
        /// Support the automatic localization.
        /// </summary>
        /// <value>The name.</value>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpMenuItem" /> is checked.
        /// Actual only for CheckBox and RadioBox style.
        /// </summary>
        /// <value><c>true</c> if checked; otherwise, <c>false</c>.</value>
        bool Checked { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpMenuItem" /> is enabled.
        /// </summary>
        /// <value><c>true</c> if enabled; otherwise, <c>false</c>.</value>
        bool Enabled { get; set; }

        /// <summary>
        /// Menu item glyph (optional).
        /// Note that image must be 32-bit with correct alpha channel.
        /// </summary>
        /// <value>The glyph.</value>
        Bitmap Glyph { get; set; }

        /// <summary>
        /// Gets or sets the parent menu item.
        /// </summary>
        /// <value>The parent.</value>
        IAimpMenuItem Parent { get; set; }

        /// <summary>
        /// Gets or sets the <see cref="MenuItemStyle" />.
        /// </summary>
        /// <value>The style.</value>
        MenuItemStyle Style { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpMenuItem" /> is visible.
        /// </summary>
        /// <value><c>true</c> if visible; otherwise, <c>false</c>.</value>
        bool Visible { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is default.
        /// Each level of menu can contains only one default item. Default item uses bold font for the text.
        /// </summary>
        /// <value><c>true</c> if this instance is default; otherwise, <c>false</c>.</value>
        bool IsDefault { get; set; }

        /// <summary>
        /// Local hotkey for menu item. Cannot be customized by end user.
        /// Refer to the <see cref="IAimpServiceActionManager.MakeHotkey" />.
        /// Refer to the <see cref="IAimpAction" />.
        /// </summary>
        /// <value>The shortcut.</value>
        int Shortcut { get; set; }

        /// <summary>
        /// Deletes the children.
        /// </summary>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult DeleteChildren();

        /// <summary>
        /// Occurs when [on show].
        /// </summary>
        event EventHandler OnShow;
    }
}
