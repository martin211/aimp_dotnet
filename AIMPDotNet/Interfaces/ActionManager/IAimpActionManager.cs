using AIMP.SDK.UI.ActionItem;

namespace AIMP.SDK.Services.ActionManager
{
    /// <summary>
    /// Action manager interface.
    /// </summary>
    public interface IAimpActionManager
    {
        /// <summary>
        /// Adds the specified action.
        /// </summary>
        /// <param name="action">The action.</param>
        void Add(AimpActionItem action);

        /// <summary>
        /// Adds the range.
        /// </summary>
        /// <param name="actions">The action collection.</param>
        void AddRange(ActionItemCollection actions);
    }
}