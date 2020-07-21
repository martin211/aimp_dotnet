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
    /// <summary>
    /// 
    /// </summary>
    public enum MenuItemPropertyType
    {
        AIMP_MENUITEM_PROPID_CUSTOM = 0,
        AIMP_MENUITEM_PROPID_ACTION = 1,
        AIMP_MENUITEM_PROPID_ID = 2,
        AIMP_MENUITEM_PROPID_NAME = 3,
        AIMP_MENUITEM_PROPID_ENABLED = 4,
        AIMP_MENUITEM_PROPID_STYLE = 5,
        AIMP_MENUITEM_PROPID_EVENT = 6,
        AIMP_MENUITEM_PROPID_EVENT_ONSHOW = 7,
        AIMP_MENUITEM_PROPID_GLYPH = 10,
        AIMP_MENUITEM_PROPID_PARENT = 11,
        AIMP_MENUITEM_PROPID_VISIBLE = 12,
        AIMP_MENUITEM_PROPID_CHECKED = 13,
        AIMP_MENUITEM_PROPID_DEFAULT = 14,
        AIMP_MENUITEM_PROPID_SHORTCUT = 15
    }

    /// <summary>
    /// AIMP Parent menu item.
    /// </summary>
    public enum ParentMenuType
    {
        CommonUtilites = 0,
        PlayerMainFunctions = 10,
        PlayerMainOpen = 11,
        PlayerMainOptions = 12,

        PlayerPlaylistAdding = 20,
        PlayerPlaylistDeletion = 21,
        PlayerPlaylistSorting = 22,
        PlayerPlaylistMiscellaneous = 23,
        PlayerPlaylistManage = 24,
        PlayerPlaylistContextAdding = 30,
        PlayerPlaylistContextQueue = 31,
        PlayerPlaylistContextFunctions = 32,
        PlayerPlaylistContextSending = 33,
        PlayerPlaylistContextDeletion = 34,

        PlayerTray = 40,
        PlayerEqLib = 41,
        PlayerStopOptions = 42,

        MlMiscellaneous = 50,
        MlDeletion = 51,

        MlMainDB = 60,
        MlMainFuntions = 61,
        MlMainOpen = 62,
        mlMainOptions = 63,

        MlTableContextAdding = 70,
        MlTableContextFunctions = 71,
        MlTableContextSending = 72,
        MlTableContextDeletion = 73,

        MlTreeContextFunctions = 80,
        MlTreeContextDeletion = 81
    }

    /// <summary>
    /// Menu manager interface.
    /// </summary>
    public interface IAimpServiceMenuManager : IAimpService
    {
        /// <summary>
        /// Adds the new menu item..
        /// </summary>
        /// <param name="parentMenuType"></param>
        /// <param name="item">Menu item <see cref="IAimpMenuItem"/>.</param>
        AimpActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem item);

        /// <summary>
        /// Adds the new menu item.
        /// </summary>
        /// <param name="item">Menu item <see cref="IAimpMenuItem"/>.</param>
        AimpActionResult Add(IAimpMenuItem item);

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="item">The menu item.</param>
        AimpActionResult Delete(IAimpMenuItem item);

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="id">The identifier.</param>
        AimpActionResult Delete(string id);

        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <param name="item">Menu item <see cref="IAimpMenuItem"/>.</param>
        AimpActionResult<IAimpMenuItem> GetById(string id);

        /// <summary>
        /// Gets the standard menu item.
        /// </summary>
        /// <param name="menuType">Type of the menu.</param>
        /// <param name="item">Menu item <see cref="IAimpMenuItem"/>.</param>
        AimpActionResult<IAimpMenuItem> GetBuiltIn(ParentMenuType menuType);
    }
}