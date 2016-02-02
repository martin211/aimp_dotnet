using AIMP.SDK.GUI.Controls.Form;

namespace AIMP.SDK.GUI.Controls
{
    public enum AimpUIButtonStyleType
    {
        AIMPUI_FLAGS_BUTTON_STYLE_NORMAL,
        AIMPUI_FLAGS_BUTTON_STYLE_DROPDOWN,
        AIMPUI_FLAGS_BUTTON_STYLE_DROPDOWNBUTTON
    }

    /// <summary>
    /// Aimp button control interface.
    /// </summary>
    public interface IAimpUIButton : IAimpUIWinControl
    {
        /// <summary>
        /// Gets or sets the caption.
        /// </summary>
        string Caption { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether [focus on click].
        /// </summary>
        bool FocusOnClick { get; set; }

        /// <summary>
        /// Gets or sets a value indicating whether this <see cref="IAimpUIButton"/> is default.
        /// </summary>
        bool Default { get; set; }

        /// <summary>
        /// Gets or sets the drop down menu.
        /// </summary>
        /// <para>
        /// Allowed only for  AIMPUI_FLAGS_BUTTON_STYLE_DROPDOWN or AIMPUI_FLAGS_BUTTON_STYLE_DROPDOWNBUTTON.
        /// </para>
        IAimpUIPopupMenu DropDownMenu { get; set; }

        /// <summary>
        /// Gets or sets the index of the image.
        /// </summary>
        int ImageIndex { get; set; }

        /// <summary>
        /// Gets or sets the image list.
        /// </summary>
        IAimpUIImageList ImageList { get; set; }

        /// <summary>
        /// Gets or sets the modal result.
        /// </summary>
        AimpModalResult ModalResult { get; set; }

        /// <summary>
        /// Gets or sets the style.
        /// </summary>
        AimpUIButtonStyleType Style { get; set; }

        /// <summary>
        /// Shows the drop down menu.
        /// </summary>
        AimpActionResult ShowDropDownMenu();
    }
}