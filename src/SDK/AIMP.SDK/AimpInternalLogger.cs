//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System;
using System.IO;
using System.Reflection;

namespace AIMP.SDK
{
    /// <summary>
    /// The Aimp internal logger class
    /// </summary>
    /// <seealso cref="IDisposable"/>
    public class AimpInternalLogger : IDisposable
    {
        private StreamWriter _streamWriter;
        private static AimpInternalLogger _instance;

        /// <summary>
        /// Gets the class instance
        /// </summary>
        public static AimpInternalLogger Instance => _instance ?? (_instance = new AimpInternalLogger());

        /// <summary>
        /// Initializes a new instance of the <see cref="AimpInternalLogger"/> class
        /// </summary>
        public AimpInternalLogger()
        {
            var logFilePath = Path.Combine(Path.GetPathRoot(Assembly.GetExecutingAssembly().Location), "aimp_dotnet.log");
            _streamWriter = new StreamWriter(logFilePath);
        }

        /// <summary>
        /// Logs the message using the specified text
        /// </summary>
        /// <param name="message">The message</param>
        public void LogMessage(string message)
        {
            _streamWriter.WriteLine(message);
            _streamWriter.Flush();
        }

        /// <summary>
        /// Disposes this instance
        /// </summary>
        public void Dispose()
        {
            _streamWriter?.Flush();
            _streamWriter?.Close();
            _streamWriter?.Dispose();
        }
    }
}
