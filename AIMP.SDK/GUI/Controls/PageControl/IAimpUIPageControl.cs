namespace AIMP.SDK.GUI.Controls.PageControl
{
    /// <summary>
    /// 
    /// </summary>
    public interface IAimpUIPageControl : IAimpUIWinControl, IAimpUIPageControlEvents
    {
        /// <summary>
        /// Gets or sets the active tab.
        /// </summary>
        IAimpUITabSheet ActiveTab { get; set; }

        /// <summary>
        /// Adds the new page tab.
        /// </summary>
        /// <param name="name">The page tab name.</param>
        /// <param name="page">The page tab.</param>
        AimpActionResult Add(string name, IAimpUITabSheet page);

        /// <summary>
        /// Deletes the specified tab.
        /// </summary>
        /// <param name="index">The index.</param>
        AimpActionResult Delete(int index);

        /// <summary>
        /// Deletes the specified page.
        /// </summary>
        /// <param name="page">The page.</param>
        AimpActionResult Delete(IAimpUITabSheet page);

        /// <summary>
        /// Gets the page tab by specified index.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="page">The page.</param>
        AimpActionResult Get(int index, out IAimpUITabSheet page);

        /// <summary>
        /// Gets the tabs count.
        /// </summary>
        int GetCount();
    }
}