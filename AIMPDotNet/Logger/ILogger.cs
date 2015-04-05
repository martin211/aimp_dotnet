using System;

namespace AIMP.SDK.Logger
{
    /// <summary>
    /// Logger interface.
    /// </summary>
    public interface ILogger
    {
        /// <summary>
        /// Writes the specified message.
        /// </summary>
        /// <param name="message">The message.</param>
        void Write(string message);

        /// <summary>
        /// Writes the specified exception.
        /// </summary>
        /// <param name="exception">The exception.</param>
        void Write(Exception exception);

        /// <summary>
        /// Closes the logger.
        /// </summary>
        void Close();
    }
}