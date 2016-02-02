using System.Drawing;

namespace AIMP.SDK.GUI.Controls
{
    public enum AimpTextAlign
    {
        LeftJustify,
        RightJustify,
        Center
    }

    public enum AimpVerticalTextAlign
    {
        Top,
        Bottom,
        Center
    }

    public enum AimpTextStyle
    {
        AIMPUI_FLAGS_FONT_BOLD,
        AIMPUI_FLAGS_FONT_ITALIC,
        AIMPUI_FLAGS_FONT_STRIKEOUT,
        AIMPUI_FLAGS_FONT_UNDERLINE
    }

    /// <summary>
    /// 
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUILabel : IAimpUIControl
    {
        /// <summary>
        /// Gets or sets a value indicating whether [automatic size].
        /// </summary>
        bool AutoSize { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [show line].
        /// </summary>
        bool ShowLine { get; set; }

        /// <summary>
        /// Gets or sets the text.
        /// </summary>
        string Text { get; set; }

        /// <summary>
        /// Gets or sets the text align.
        /// </summary>
        AimpTextAlign TextAlign { get; set; }

        /// <summary>
        /// Gets or sets the vertical text align.
        /// </summary>
        AimpVerticalTextAlign VerticalTextAlign { get; set; }

        /// <summary>
        /// Gets or sets the color of the text.
        /// </summary>
        Color TextColor { get; set; }

        /// <summary>
        /// Gets or sets the text style.
        /// </summary>
        AimpTextStyle TextStyle { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUILabel"/> is transparent.
        /// </summary>
        bool Transparent { get; set; }

        /// <summary>
        /// Gets or sets the URL.
        /// </summary>
        string Url { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [word wrap].
        /// </summary>
        bool WordWrap { get; set; }
    }
}