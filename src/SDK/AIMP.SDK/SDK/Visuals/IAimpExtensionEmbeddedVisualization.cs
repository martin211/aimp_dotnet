//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2022 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;

namespace AIMP.SDK.Visuals
{
    /// <summary>
    /// Enum AimpVisualClickButtonType
    /// </summary>
    public enum AimpVisualClickButtonType
    {
        /// <summary>
        /// The aimp visual click button left
        /// </summary>
        LeftButton,

        /// <summary>
        /// The aimp visual click button middle
        /// </summary>
        MiddleButton
    }

    /// <summary>
    /// This type visualization displays on visual display of player only and can be chosen by user.
    /// <para>
    /// Instance should be created by plugin and must be registered in the application in the
    /// <see cref="AimpPlugin.Initialize" /> method via the <see cref="IAimpCore.RegisterExtension" /> method.
    /// </para>
    /// Implements the <see cref="AIMP.SDK.IAimpExtension" />
    /// </summary>
    /// <seealso cref="AIMP.SDK.IAimpExtension" />
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
        /// Returns zero or combination of followed flags <seealso cref="AimpVisualFlags" />.
        /// </summary>
        /// <returns>AimpVisualFlags.</returns>
        AimpVisualFlags GetFlags();

        /// <summary>
        /// Method returns a maximal resolution supported by the extension. If current resolution is not supported by
        /// extension, player will automatically stretch output.
        /// </summary>
        /// <returns>Item1 is width, Item2 is height.</returns>
        AimpActionResult<int, int> GetMaxDisplaySize();

        /// <summary>
        /// Gets the visualization display name.
        /// </summary>
        /// <returns>AimpActionResult&lt;System.String&gt;.</returns>
        AimpActionResult<string> GetName();

        /// <summary>
        /// Initializes the visualization. Occurs when user activate the visualization.
        /// </summary>
        /// <param name="width">The width.</param>
        /// <param name="height">The height.</param>
        /// <returns>AimpActionResult.</returns>
        AimpActionResult Initialize(int width, int height);

        /// <summary>
        /// Called when visualization should be finalized.
        /// </summary>
        void OnFinalize();

        /// <summary>
        /// Draws visualization on the specified output screen.
        /// </summary>
        /// <param name="dc">The output screen handle.</param>
        /// <param name="data">The visualization data <seealso cref="AimpVisualData" />.</param>
        void Draw(IntPtr dc, AimpVisualData data);
    }
}
