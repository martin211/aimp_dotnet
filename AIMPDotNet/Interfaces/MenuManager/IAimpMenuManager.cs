using AIMP.SDK.UI.MenuItem;

namespace AIMP.SDK.Services.MenuManager
{
    /// <summary>
    /// 
    /// </summary>
    public enum MenuItemPropertyType
    {
        AIMP_MENUITEM_PROPID_CUSTOM = 0,
        AIMP_MENUITEM_PROPID_ACTION,
        AIMP_MENUITEM_PROPID_ID,
        AIMP_MENUITEM_PROPID_NAME,
        AIMP_MENUITEM_PROPID_ENABLED,
        AIMP_MENUITEM_PROPID_STYLE,
        AIMP_MENUITEM_PROPID_EVENT,
        AIMP_MENUITEM_PROPID_EVENT_ONSHOW,
        AIMP_MENUITEM_PROPID_GLYPH,
        AIMP_MENUITEM_PROPID_PARENT,
        AIMP_MENUITEM_PROPID_VISIBLE,
        AIMP_MENUITEM_PROPID_CHECKED
    }

    public enum MenuItemStyleType
    {
        AIMP_MENUITEM_STYLE_NORMAL = 0,
        AIMP_MENUITEM_STYLE_CHECKBOX,
        AIMP_MENUITEM_STYLE_RADIOBOX
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
        AIMP_MENUID_PLAYER_EQ_LIB = 41
    }

    /// <summary>
    /// Menu manager interface.
    /// </summary>
    public interface IAimpMenuManager
    {
        /// <summary>
        /// Adds the menu item.
        /// </summary>
        /// <param name="parentMenuType">Type of the parent menu.</param>
        /// <param name="items">The menu item <see cref="MenuItem" />.</param>
        void AddRange(ParentMenuType parentMenuType, MenuItemCollection items);
        
        /// <summary>
        /// Adds new menu item.
        /// </summary>
        /// <param name="parentMenuType"></param>       b 
        /// <param name="item"></param>
        void Add(ParentMenuType parentMenuType, MenuItem item);

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="item">The menu item.</param>
        void Delete(MenuItem item);

        /// <summary>
        /// Deletes the menu item.
        /// </summary>
        /// <param name="id">The identifier.</param>
        void Delete(string id);

        /// <summary>
        /// Deletes the specified items.
        /// </summary>
        /// <param name="items">The items.</param>
        void Delete(MenuItemCollection items);

        /// <summary>
        /// Gets the by identifier.
        /// </summary>
        /// <param name="id">The identifier.</param>
        /// <returns></returns>
        MenuItem GetById(string id);

        /// <summary>
        /// Gets the standart menu item.
        /// </summary>
        /// <param name="menuType">Type of the menu.</param>
        MenuItem GetBuiltIn(ParentMenuType menuType);
    }
}