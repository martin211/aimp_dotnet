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

    public enum MenuItemStyleType
    {
        AIMP_MENUITEM_STYLE_NORMAL = 0,
        AIMP_MENUITEM_STYLE_CHECKBOX = 1,
        AIMP_MENUITEM_STYLE_RADIOBOX = 2
    }

    /// <summary>
    /// AIMP Parent menu item.
    /// </summary>
    public enum ParentMenuType
    {
        AIMP_MENUID_COMMON_UTILITIES = 0,
        AIMP_MENUID_PLAYER_MAIN_FUNCTIONS = 10,
        AIMP_MENUID_PLAYER_MAIN_OPEN = 11,
        AIMP_MENUID_PLAYER_MAIN_OPTIONS = 12,

        AIMP_MENUID_PLAYER_PLAYLIST_ADDING = 20,
        AIMP_MENUID_PLAYER_PLAYLIST_DELETION = 21,
        AIMP_MENUID_PLAYER_PLAYLIST_SORTING = 22,
        AIMP_MENUID_PLAYER_PLAYLIST_MISCELLANEOUS = 23,
        AIMP_MENUID_PLAYER_PLAYLIST_MANAGE = 24,
        AIMP_MENUID_PLAYER_PLAYLIST_CONTEXT_ADDING = 30,
        AIMP_MENUID_PLAYER_PLAYLIST_CONTEXT_QUEUE = 31,
        AIMP_MENUID_PLAYER_PLAYLIST_CONTEXT_FUNCTIONS = 32,
        AIMP_MENUID_PLAYER_PLAYLIST_CONTEXT_SENDING = 33,
        AIMP_MENUID_PLAYER_PLAYLIST_CONTEXT_DELETION = 34,

        AIMP_MENUID_PLAYER_TRAY = 40,
        AIMP_MENUID_PLAYER_EQ_LIB = 41,
        AIMP_MENUID_PLAYER_STOP_OPTIONS = 42,

        AIMP_MENUID_ML_MISCELLANEOUS = 50,
        AIMP_MENUID_ML_DELETION = 51,

        AIMP_MENUID_ML_MAIN_DB = 60,
        AIMP_MENUID_ML_MAIN_FUNCTIONS = 61,
        AIMP_MENUID_ML_MAIN_OPEN = 62,
        AIMP_MENUID_ML_MAIN_OPTIONS = 63,

        AIMP_MENUID_ML_TABLE_CONTEXT_ADDING = 70,
        AIMP_MENUID_ML_TABLE_CONTEXT_FUNCTIONS = 71,
        AIMP_MENUID_ML_TABLE_CONTEXT_SENDING = 72,
        AIMP_MENUID_ML_TABLE_CONTEXT_DELETION = 73,

        AIMP_MENUID_ML_TREE_CONTEXT_FUNCTIONS = 80,
        AIMP_MENUID_ML_TREE_CONTEXT_DELETION = 81
    }

    /// <summary>
    /// Menu manager interface.
    /// </summary>
    public interface IAimpMenuManager
    {
        ///// <summary>
        ///// Adds the menu item.
        ///// </summary>
        ///// <param name="parentMenuType">Type of the parent menu.</param>
        ///// <param name="items">The menu item <see cref="MenuItem" />.</param>
        //void AddRange(ParentMenuType parentMenuType, MenuItemCollection items);

        AimpActionResult CreateMenuItem(out IAimpMenuItem item);

        /// <summary>
        /// Adds new menu item.
        /// </summary>
        /// <param name="parentMenuType"></param>
        /// <param name="item"></param>
        AimpActionResult Add(ParentMenuType parentMenuType, IAimpMenuItem item);

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

        ///// <summary>
        ///// Deletes the specified items.
        ///// </summary>
        ///// <param name="items">The items.</param>
        //void Delete(MenuItemCollection items);

        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns></returns>
        AimpActionResult GetById(string id, out IAimpMenuItem item);

        /// <summary>
        /// Gets the standard menu item.
        /// </summary>
        /// <param name="menuType">Type of the menu.</param>
        AimpActionResult GetBuiltIn(ParentMenuType menuType, out IAimpMenuItem item);
    }
}