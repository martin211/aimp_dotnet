using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace dotNetInteropPlugin.PluginDev
{

    /// <summary>
    /// Working with track Cover Art
    /// </summary>
    public interface IMAIMPCoverArtManager
    {
        /// <summary>
        /// Load cover art from file as bitmap (cover art will be proportional scaled to bitmap size)
        /// </summary>
        /// <param name="FileName">Path to file</param>
        /// <param name="sz">Size of result bitmap</param>
        /// <returns>Loaded cover art</returns>
        Bitmap LoadCoverArtForFile(string FileName, Size sz);
        /// <summary>
        /// Load cover art from file as bitmap (cover art will be proportional scaled to bitmap size)
        /// </summary>
        /// <param name="FileName">Path to file</param>
        /// <param name="Width">width of result bitmap</param>
        /// <param name="Height">Height of result bitmap</param>
        /// <returns>Loaded cover art</returns>
        Bitmap LoadCoverArtForFile(string FileName, int Width, int Height);

        /// <summary>
        /// Draw current cover art on Graphics inside Rectangle 
        /// </summary>
        /// <param name="gr">Graphics, where drawing cover art</param>
        /// <param name="rct">Rectangle, inside witch cover art will be drawn</param>
        /// <returns>Success</returns>
        bool DrawCurrentCoverArt(Graphics gr, Rectangle rct);
        /// <summary>
        /// Get current Cover Art as bitmap. Result will be proportional scaled to size.
        /// </summary>
        /// <param name="sz">Size of bitmap</param>
        /// <returns>Cover Art</returns>
        Bitmap GetCurrentCoverArt(Size sz);
        /// <summary>
        /// Get current Cover Art as bitmap. Result will be proportional scaled to size.
        /// </summary>
        /// <param name="Width">Width of bitmap</param>
        /// <param name="Height">Height of bitmap</param>
        /// <returns>Cover Art</returns>
        Bitmap GetCurrentCoverArt(int Width, int Height);
        /// <summary>
        /// Get current Cover Art as bitmap.
        /// </summary>
        /// <returns>Cover Art</returns>
        Bitmap GetCurrentCoverArt();

        /// <summary>
        /// Size of current cover art (null if doesn't exist)
        /// </summary>
        Size? CurrentCoverArtSize { get; }
        /// <summary>
        /// Cover Art existence
        /// </summary>
        bool HasCoverArt { get; }

        /// <summary>
        /// Perform proportional correctness of size to current cover art
        /// </summary>
        /// <param name="sz">Corrected size</param>
        /// <returns>Success</returns>
        bool ProportionalSizeCorrection(ref Size sz);
        /// <summary>
        /// Perform proportional correctness of size to current cover art
        /// </summary>
        /// <param name="width">Corrected width</param>
        /// <param name="height">Corrected height</param>
        /// <returns>Success</returns>
        bool ProportionalSizeCorrection(ref int width, ref int height);
    }
}
