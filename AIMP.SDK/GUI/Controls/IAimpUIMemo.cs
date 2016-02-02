using System.Drawing;
using System.IO;

namespace AIMP.SDK.GUI.Controls
{
    /// <summary>
    /// 
    /// </summary>
    // ReSharper disable once InconsistentNaming
    public interface IAimpUIMemo : IAimpUIBaseEdit
    {
        /// <summary>
        /// Gets or sets the position.
        /// </summary>
        Point Position { get; set; }

        /// <summary>
        /// Adds the line.
        /// </summary>
        /// <param name="text">The text.</param>
        AimpActionResult AddLine(string text);

        /// <summary>
        /// Clears text.
        /// </summary>
        AimpActionResult Clear();

        /// <summary>
        /// Deletes the line.
        /// </summary>
        /// <param name="lineIndex">Index of the line.</param>
        AimpActionResult DeleteLine(int lineIndex);

        /// <summary>
        /// Inserts the line.
        /// </summary>
        /// <param name="lineIndex">Index of the line.</param>
        /// <param name="text">The text.</param>
        AimpActionResult InsertLine(int lineIndex, string text);

        /// <summary>
        /// Gets the line.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="text">The text.</param>
        AimpActionResult GetLine(int index, out string text);

        /// <summary>
        /// Sets the line.
        /// </summary>
        /// <param name="index">The index.</param>
        /// <param name="text">The text.</param>
        AimpActionResult SetLine(int index, string text);

        /// <summary>
        /// Gets the line count.
        /// </summary>
        int GetLineCount();

        /// <summary>
        /// Loads from file.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        AimpActionResult LoadFromFile(string fileName);

        /// <summary>
        /// Loads from stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        AimpActionResult LoadFromStream(Stream stream);

        /// <summary>
        /// Saves to file.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        AimpActionResult SaveToFile(string fileName);

        /// <summary>
        /// Saves to stream.
        /// </summary>
        /// <param name="stream">The stream.</param>
        AimpActionResult SaveToStream(Stream stream);
    }
}