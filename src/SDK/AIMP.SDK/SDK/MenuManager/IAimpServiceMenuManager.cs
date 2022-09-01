//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.MenuManager.Objects;

namespace AIMP.SDK.MenuManager
{
    /// <summary>
    /// AIMP Parent menu item.
    /// </summary>
    public enum ParentMenuType
    {
        /// <summary>
        /// The common utilities
        /// </summary>
        CommonUtilities = 0,

        /// <summary>
        /// The player main functions
        /// </summary>
        PlayerMainFunctions = 10,

        /// <summary>
        /// The player main open
        /// </summary>
        PlayerMainOpen = 11,

        /// <summary>
        /// The player main options
        /// </summary>
        PlayerMainOptions = 12,

        /// <summary>
        /// The player playlist adding
        /// </summary>
        PlayerPlaylistAdding = 20,

        /// <summary>
        /// The player playlist deletion
        /// </summary>
        PlayerPlaylistDeletion = 21,

        /// <summary>
        /// The player playlist sorting
        /// </summary>
        PlayerPlaylistSorting = 22,

        /// <summary>
        /// The player playlist miscellaneous
        /// </summary>
        PlayerPlaylistMiscellaneous = 23,

        /// <summary>
        /// The player playlist manage
        /// </summary>
        PlayerPlaylistManage = 24,

        /// <summary>
        /// The player playlist context adding
        /// </summary>
        PlayerPlaylistContextAdding = 30,

        /// <summary>
        /// The player playlist context queue
        /// </summary>
        PlayerPlaylistContextQueue = 31,

        /// <summary>
        /// The player playlist context functions
        /// </summary>
        PlayerPlaylistContextFunctions = 32,

        /// <summary>
        /// The player playlist context sending
        /// </summary>
        PlayerPlaylistContextSending = 33,

        /// <summary>
        /// The player playlist context deletion
        /// </summary>
        PlayerPlaylistContextDeletion = 34,

        /// <summary>
        /// The player tray
        /// </summary>
        PlayerTray = 40,

        /// <summary>
        /// The player eq library
        /// </summary>
        PlayerEqLib = 41,

        /// <summary>
        /// The player stop options
        /// </summary>
        PlayerStopOptions = 42,

        /// <summary>
        /// The ml miscellaneous
        /// </summary>
        MlMiscellaneous = 50,

        /// <summary>
        /// The ml deletion
        /// </summary>
        MlDeletion = 51,

        /// <summary>
        /// The ml main database
        /// </summary>
        MlMainDB = 60,

        /// <summary>
        /// The ml main funtions
        /// </summary>
        MlMainFunctions = 61,

        /// <summary>
        /// The ml main open
        /// </summary>
        MlMainOpen = 62,

        /// <summary>
        /// The ml main options
        /// </summary>
        mlMainOptions = 63,

        /// <summary>
        /// The ml table context adding
        /// </summary>
        MlTableContextAdding = 70,

        /// <summary>
        /// The ml table context functions
        /// </summary>
        MlTableContextFunctions = 71,

        /// <summary>
        /// The ml table context sending
        /// </summary>
        MlTableContextSending = 72,

        /// <summary>
        /// The ml table context deletion
        /// </summary>
        MlTableContextDeletion = 73,

        /// <summary>
        /// The ml tree context functions
        /// </summary>
        MlTreeContextFunctions = 80,

        /// <summary>
        /// The ml tree context deletion
        /// </summary>
        MlTreeContextDeletion = 81
    }

    /// <summary>
    /// Menu manager interface.
    /// Implements the <see cref="AIMP.SDK.IAimpService" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpService" />
    public interface IAimpServiceMenuManager : IAimpService
    {
        /// <summary>
        /// Adds the new menu item..
        /// </summary>
        /// <param name="parentMenuType">Type of the parent menu.</param>
        /// <param name="item">Menu item <see cref="IAimpMenuItem" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem item);

        /// <summary>
        /// Adds the new menu item.
        /// </summary>
        /// <param name="item">Menu item <see cref="IAimpMenuItem" />.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Add(IAimpMenuItem item);

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="item">The menu item.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(IAimpMenuItem item);

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Delete(string id);

        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns>AimpActionResult&lt;IAimpMenuItem&gt;.</returns>
        AimpActionResult<IAimpMenuItem> GetById(string id);

        /// <summary>
        /// Gets the standard menu item.
        /// </summary>
        /// <param name="menuType">Type of the menu.</param>
        /// <returns>AimpActionResult&lt;IAimpMenuItem&gt;.</returns>
        AimpActionResult<IAimpMenuItem> GetBuiltIn(ParentMenuType menuType);
    }
}
