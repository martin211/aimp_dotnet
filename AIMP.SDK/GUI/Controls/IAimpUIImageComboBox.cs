namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// Image button control interface.
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIImageComboBox : IAimpUIBaseComboBox
    {
        /// <summary>
        /// Gets or sets the image list.
        /// </summary>
        IAimpUIImageList ImageList { get; set; }

        /// <summary>
        /// Gets or sets the index of the image.
        /// </summary>
        int ImageIndex { get; set; }

        /// <summary>
        /// Adds the specified value.
        /// </summary>
        /// <param name="value">The value.</param>
        /// <param name="imageIndex">Index of the image.</param>
        AimpActionResult Add(string value, int imageIndex);

        /// <summary>
        /// Gets the index of the image.
        /// </summary>
        int GetImageIndex();

        /// <summary>
        /// Sets the index of the image.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="imageIndex">Index of the image.</param>
        AimpActionResult SetImageIndex(int index, int imageIndex);
    }
}