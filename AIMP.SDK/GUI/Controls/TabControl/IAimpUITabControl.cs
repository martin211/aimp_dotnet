namespace AIMP.SDK.GUI.Controls.TabControl
{
    public interface IAimpUITabControl : IAimpUIWinControl, IAimpUITabControlEvents
    {
        /// <summary>
        /// Gets or sets the index of the active tab.
        /// </summary>
        /// <value>
        /// The index of the active tab.
        /// </value>
        int ActiveTabIndex { get; set; }

        AimpActionResult Add(string name);

        AimpActionResult Delete(int index);

        AimpActionResult Get(int index, out string text);

        int GetCount();
    }
}