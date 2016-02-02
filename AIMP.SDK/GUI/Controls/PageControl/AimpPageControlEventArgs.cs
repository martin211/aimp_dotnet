using System;

namespace AIMP.SDK.GUI.Controls.PageControl
{
    /// <summary>
    /// 
    /// </summary>
    public class AimpPageControlEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpPageControlEventArgs"/> class.
        /// </summary>
        /// <param name="tabSheet">The tab sheet.</param>
        public AimpPageControlEventArgs(IAimpUITabSheet tabSheet)
        {
            TabSheet = tabSheet;
        }

        /// <summary>
        /// Gets the tab sheet.
        /// </summary>
        public IAimpUITabSheet TabSheet { get; private set; }
    }
}