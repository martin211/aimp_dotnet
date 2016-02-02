using AIMP.SDK.GUI.Controls.Events;

namespace AIMP.SDK.GUI.Controls
{
    public interface IAimpUISplitter : IAimpUIControl, IAimpUIDrawEvents
    {
        /// <summary>
        /// Gets or sets a value indicating whether this instance can hide.
        /// </summary>
        /// <value>
        ///   <c>true</c> if this instance can hide; otherwise, <c>false</c>.
        /// </value>
        bool CanHide { get; set; }

        /// <summary>
        /// Gets or sets the control.
        /// </summary>
        /// <value>
        /// The control.
        /// </value>
        IAimpUIControl Control { get; set; }
    }
}