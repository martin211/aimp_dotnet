using System;

namespace AIMP.SDK.Visuals
{
    public enum AimpVisualClickButtonType
    {
        AIMP_VISUAL_CLICK_BUTTON_LEFT,
        AIMP_VISUAL_CLICK_BUTTON_MIDDLE
    }

    /// <summary>
    ///  This type visualization displays on visual display of player only and can be chosen by user. 
    /// </summary>
    public interface IAimpExtensionEmbeddedVisualization : IAimpExtension
    {
        /// <summary>
        /// Occurs when user clicked on visualization.
        /// </summary>
        /// <param name="x">Position by X.</param>
        /// <param name="y">Position by Y.</param>
        /// <param name="button">The mouse button.</param>
        void Click(int x, int y, AimpVisualClickButtonType button);

        /// <summary>
        /// Occurs when the sizes of the visualization window are changed.
        /// </summary>
        /// <param name="newWidth">The new width.</param>
        /// <param name="newHeight">The new height.</param>
        void Resize(int newWidth, int newHeight);

        /// <summary>
        /// Returns zero or combination of followed flags <seealso cref="AimpVisualFlags"/>.
        /// </summary>
        AimpVisualFlags GetFlags();

        /// <summary>
        /// Method returns a maximal resolution supported by the extension. If current resolution is not supported by extension, player will automatically stretch output.
        /// </summary>
        /// <param name="width">The width.</param>
        /// <param name="height">The height.</param>
        AimpActionResult GetMaxDisplaySize(out int width, out int height);

        /// <summary>
        /// Gets the visualization display name.
        /// </summary>
        /// <param name="name">The display name.</param>
        AimpActionResult GetName(out string name);

        /// <summary>
        /// Initializes the visualization. Occurs when user activate the visualization.
        /// </summary>
        /// <param name="width">The width.</param>
        /// <param name="height">The height.</param>
        /// <returns></returns>
        AimpActionResult Initialize(int width, int height);

        /// <summary>
        /// Called when visualization should be finalized.
        /// </summary>
        void OnFinalize();

        /// <summary>
        /// Draws visualization on the specified output screen.
        /// </summary>
        /// <param name="dc">The output screen handle.</param>
        /// <param name="data">The visualization data <seealso cref="AimpVisualData"/>.</param>
        void Draw(IntPtr dc, AimpVisualData data);
    }
}