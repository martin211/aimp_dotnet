//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.Drawing;

namespace AIMP.SDK.Objects
{
    /// <summary>
    /// The aimp image format enum
    /// </summary>
    public enum AimpImageFormat
    {
        /// <summary>
        /// Unknown
        /// </summary>
        Unknown = 0,
        /// <summary>
        /// Bpm
        /// </summary>
        BPM = 1,
        /// <summary>
        /// Gif
        /// </summary>
        GIF = 2,
        /// <summary>
        /// Jpg
        /// </summary>
        JPG = 3,
        /// <summary>
        /// Png
        /// </summary>
        PNG = 4
    }

    /// <summary>
    /// The Aimp image interface
    /// </summary>
    /// <seealso cref="IAimpObject"/>
    /// <seealso cref="IAimpImage2"/>
    public interface IAimpImage : IAimpObject, IAimpImage2
    {
        /// <summary>
        /// Gets the value of the <see cref="AimpImageFormat"/>. 
        /// </summary>
        AimpImageFormat FormatId { get; }

        /// <summary>
        /// Gets the value of the image size.
        /// </summary>
        PointF Size { get; }

        /// <summary>
        /// Loads the image from file using the specified file name.
        /// </summary>
        /// <param name="fileName">The file name</param>
        /// <returns>The aimp action result</returns>
        AimpActionResult LoadFromFile(string fileName);

        /// <summary>
        /// Loads the image from <see cref="IAimpStream"/> stream
        /// </summary>
        /// <param name="stream">The stream</param>
        /// <returns>The aimp action result</returns>
        AimpActionResult LoadFromStream(IAimpStream stream);

        /// <summary>
        /// Saves the image to the specified file name
        /// </summary>
        /// <param name="fileName">The file name</param>
        /// <param name="format">The format</param>
        /// <returns>The aimp action result</returns>
        AimpActionResult SaveToFile(string fileName, AimpImageFormat format);

        /// <summary>
        /// Saves the to <see cref="IAimpStream"/>.
        /// </summary>
        /// <param name="stream">The stream</param>
        /// <param name="format">The format</param>
        /// <returns>The aimp action result</returns>
        AimpActionResult SaveToStream(IAimpStream stream, AimpImageFormat format);

        /// <summary>
        /// Clones this instance
        /// </summary>
        /// <returns>An aimp action result of i aimp image</returns>
        AimpActionResult<IAimpImage> Clone();

        /// <summary>
        /// Draws image on the specified canvas.
        /// </summary>
        /// <param name="dc">The canvas handle</param>
        /// <param name="rect">The target rect</param>
        /// <returns>The aimp action result</returns>
        AimpActionResult Draw(IntPtr dc, RectangleF rect);

        /// <summary>
        /// Resizes the width
        /// </summary>
        /// <param name="width">The new width</param>
        /// <param name="height">The new height</param>
        /// <returns>The aimp action result</returns>
        AimpActionResult Resize(int width, int height);
    }
}
