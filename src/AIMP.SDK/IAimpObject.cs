// ----------------------------------------------------
// 
// AIMP DotNet SDK
// 
// Copyright (c) 2014 - 2020 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;

namespace AIMP.SDK
{
    /// <summary>
    /// Class AimpErrorArgs.
    /// Implements the <see cref="System.EventArgs" />
    /// </summary>
    /// <seealso cref="System.EventArgs" />
    public class AimpErrorArgs : EventArgs
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="AimpErrorArgs" /> class.
        /// </summary>
        /// <param name="aimpActionResult">The aimp action result.</param>
        /// <param name="message">The message.</param>
        public AimpErrorArgs(ActionResultType aimpActionResult, string message)
        {
            ActionResultType = aimpActionResult;
            Message = message;
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpErrorArgs" /> class.
        /// </summary>
        /// <param name="aimpActionResult">The aimp action result.</param>
        /// <param name="message">The message.</param>
        /// <param name="stackTrace">The stack trace.</param>
        public AimpErrorArgs(ActionResultType aimpActionResult, string message, string stackTrace) : this(
            aimpActionResult, message)
        {
            StackTrace = stackTrace;
        }

        /// <summary>
        /// Gets the type of the action result.
        /// </summary>
        /// <value>The type of the action result.</value>
        public ActionResultType ActionResultType { get; }

        /// <summary>
        /// Gets the message.
        /// </summary>
        /// <value>The message.</value>
        public string Message { get; }

        /// <summary>
        /// Gets or sets the stack trace.
        /// </summary>
        /// <value>The stack trace.</value>
        public string StackTrace { get; set; }
    }

    /// <summary>
    /// Interface IAimpObject
    /// </summary>
    public interface IAimpObject : IDisposable
    {
    }
}
