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

namespace AIMP.SDK.MenuManager
{
    using System.Drawing;
    using ActionManager;

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
    /// </summary>
    public interface IAimpMenuItem : IAimpActionEvent, IAimpObject
    {
        /// <summary>
        /// This is a user data parameter.
        /// It allow you to bind custom data to the interface.
        /// </summary>
        string Custom { get; set; }

        /// <summary>
        /// Provides an ability to set the <see cref="IAimpAction"/> for menu item.
        /// Menu item will inherits the Name, Enabled, OnExecute event from the action.
        /// </summary>
        IAimpAction Action { get; set; }

        /// <summary>
        /// Gets or sets the identifier.
        /// Must be unique for all plugins.
        /// </summary>
        string Id { get; set; }

        /// <summary>
        /// Gets or sets the menu item display name.
        /// Support the automatic localization.
        /// </summary>
        string Name { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpMenuItem"/> is checked.
        /// Actual only for CheckBox and RadioBox style.
        /// </summary>
        bool Checked { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpMenuItem"/> is enabled.
        /// </summary>
        bool Enabled { get; set; }

        /// <summary>
        /// Menu item glyph (optional).
        /// Note that image must be 32-bit with correct alpha channel.
        /// </summary>
        Bitmap Glyph { get; set; }

        /// <summary>
        /// Gets or sets the parent menu item.
        /// </summary>
        IAimpMenuItem Parent { get; set; }

        /// <summary>
        /// Gets or sets the <see cref="MenuItemStyle"/>.
        /// </summary>
        MenuItemStyle Style { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpMenuItem"/> is visible.
        /// </summary>
        bool Visible { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is default.
        /// Each level of menu can contains only one default item. Default item uses bold font for the text.
        /// </summary>
        bool IsDefault { get; set; }

        /// <summary>
        /// Local hotkey for menu item. Cannot be customized by end user.
        /// Refer to the <see cref="IAimpServiceActionManager.MakeHotkey"/>.
        /// Refer to the <see cref="IAimpAction"/>.
        /// </summary>
        int Shortcut { get; set; }

        /// <summary>
        /// Deletes the children.
        /// </summary>
        AimpActionResult DeleteChildren();

        event EventHandler OnShow;
    }
}