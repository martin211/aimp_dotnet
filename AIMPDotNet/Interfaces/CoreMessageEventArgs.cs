namespace AIMP.Proxy.Infrastructure.Interfaces
{
    using System;

    /// <summary>
    /// AIMP Event Information
    /// </summary>
    [Serializable]
    public class CoreMessageEventArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="CoreMessageEventArgs"/> class.
        /// </summary>
        /// <param name="message">The message.</param>
        /// <param name="value">The value.</param>
        /// <param name="result">The result.</param>
        public CoreMessageEventArgs(uint message, int value, long result)
        {
            Message = message;
            Value = value;
            Result = result;
        }

        /// <summary>
        /// Gets the message code.
        /// </summary>
        public uint Message { get; private set; }

        /// <summary>
        /// Gets the value.
        /// </summary>
        public int Value { get; private set; }

        /// <summary>
        /// Gets the result.
        /// </summary>
        /// <value>
        /// The result.
        /// </value>
        public long Result { get; private set; }
    }
}