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
    ///     Class AimpActionException.
    ///     Implements the <see cref="System.Exception" />
    /// </summary>
    /// <seealso cref="System.Exception" />
    public class AimpActionException : Exception
    {
        /// <summary>
        ///     Initializes a new instance of the <see cref="AimpActionException" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        public AimpActionException(ActionResultType resultType)
        {
            ResultType = resultType;
        }

        /// <summary>
        ///     Initializes a new instance of the <see cref="AimpActionException" /> class.
        /// </summary>
        /// <param name="resultType">Type of the result.</param>
        /// <param name="message">The message.</param>
        public AimpActionException(ActionResultType resultType, string message) : base(message)
        {
            ResultType = resultType;
        }

        /// <summary>
        ///     Gets the type of the result.
        /// </summary>
        /// <value>The type of the result.</value>
        public ActionResultType ResultType { get; }
    }
}