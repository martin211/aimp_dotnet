using AIMP.SDK.MenuManager.Objects;

namespace AIMP.SDK.MenuManager;

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