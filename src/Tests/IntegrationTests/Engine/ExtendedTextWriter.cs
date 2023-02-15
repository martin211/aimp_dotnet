﻿//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.IO;

namespace Aimp.TestRunner.Engine;

/// <summary>
///     ExtendedTextWriter extends the TextWriter abstract class
///     to support displaying text in color.
/// </summary>
public abstract class ExtendedTextWriter : TextWriter
{
    /// <summary>
    ///     Writes the value with the specified style.
    /// </summary>
    /// <param name="style">The style.</param>
    /// <param name="value">The value.</param>
    public abstract void Write(ColorStyle style, string value);

    /// <summary>
    ///     Writes the value with the specified style
    /// </summary>
    /// <param name="style">The style.</param>
    /// <param name="value">The value.</param>
    public abstract void WriteLine(ColorStyle style, string value);

    /// <summary>
    ///     Writes the label and the option that goes with it.
    /// </summary>
    /// <param name="label">The label.</param>
    /// <param name="option">The option.</param>
    public abstract void WriteLabel(string label, object option);

    /// <summary>
    ///     Writes the label and the option that goes with it.
    /// </summary>
    /// <param name="label">The label.</param>
    /// <param name="option">The option.</param>
    /// <param name="valueStyle">The color to display the value with</param>
    public abstract void WriteLabel(string label, object option, ColorStyle valueStyle);

    /// <summary>
    ///     Writes the label and the option that goes with it followed by a new line.
    /// </summary>
    /// <param name="label">The label.</param>
    /// <param name="option">The option.</param>
    public abstract void WriteLabelLine(string label, object option);

    /// <summary>
    ///     Writes the label and the option that goes with it followed by a new line.
    /// </summary>
    /// <param name="label">The label.</param>
    /// <param name="option">The option.</param>
    /// <param name="valueStyle">The color to display the value with</param>
    public abstract void WriteLabelLine(string label, object option, ColorStyle valueStyle);
}
