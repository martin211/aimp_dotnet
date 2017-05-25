// ----------------------------------------------------
// 
// AIMP DotNet SDK
//  
// Copyright (c) 2014 - 2017 Evgeniy Bogdan
// https://github.com/martin211/aimp_dotnet
// 
// Mail: mail4evgeniy@gmail.com
// 
// ----------------------------------------------------

using System;
using System.Collections.Generic;
using System.IO;

namespace AIMP.SDK.Logger
{
    /// <summary>
    /// 
    /// </summary>
    public class Logger : IDisposable, ILogger
    {
        private static Queue<Log> _logQueue;
        private static int _maxLogAge = 10;
        private static int _queueSize = 10;
        private static DateTime lastFlushed = DateTime.Now;
        private bool _disposed;
        private string _fileLogPath;
        private string _fileName;
        private bool _initialized;
        private string _logDir;

        /// <summary>
        /// Performs application-defined tasks associated with freeing, releasing, or resetting unmanaged resources.
        /// </summary>
        public void Dispose()
        {
            FlushLog();
            _disposed = true;
        }

        /// <summary>
        /// Closes this instance.
        /// </summary>
        public void Close()
        {
            Dispose();
        }

        /// <summary>
        /// Writes to log.
        /// </summary>
        /// <param name="message">The message.</param>
        public void Write(string message)
        {
            WriteToLog(message);
        }

        /// <summary>
        /// Writes the specified exception.
        /// </summary>
        /// <param name="exception">The exception.</param>
        public void Write(Exception exception)
        {
            WriteToLog(exception.ToString());
        }


        /// <summary>
        /// Finalizes an instance of the <see cref="Logger"/> class.
        /// </summary>
        ~Logger()
        {
            if (!_disposed)
            {
                FlushLog();
            }
        }

        /// <summary>
        /// Initializes the specified log dir.
        /// </summary>
        /// <param name="logDir">The log dir.</param>
        /// <param name="fileName">Name of the file.</param>
        public void Initialize(string logDir, string fileName)
        {
            _logDir = logDir;
            _fileName = fileName;
            _logQueue = new Queue<Log>(_queueSize);
            _initialized = true;

            _fileLogPath = string.Format("{0}{1}_{2}", _logDir, DateTime.Now.ToString("yyyy-MM-dd"), _fileName);

            if (!File.Exists(_fileLogPath))
            {
                File.Create(_fileLogPath);
            }
        }

        private void WriteToLog(string message)
        {
            if (!_initialized)
            {
                throw new ApplicationException("Logger has not been initialized.");
            }

            // Lock the queue while writing to prevent contention for the log file
            lock (_logQueue)
            {
                // Create the entry and push to the Queue
                Log logEntry = new Log(message);
                _logQueue.Enqueue(logEntry);

                // If we have reached the Queue Size then flush the Queue
                if (_logQueue.Count >= _queueSize || DoPeriodicFlush())
                {
                    FlushLog();
                }
            }
        }

        private bool DoPeriodicFlush()
        {
            TimeSpan logAge = DateTime.Now - lastFlushed;
            if (logAge.TotalMinutes >= _maxLogAge)
            {
                lastFlushed = DateTime.Now;
                return true;
            }
            return false;
        }

        private void FlushLog()
        {
            using (var stream = new FileStream(_fileLogPath, FileMode.OpenOrCreate))
            {
                stream.Seek(stream.Length, SeekOrigin.Begin);
                using (var sw = new StreamWriter(stream))
                {
                    while (_logQueue.Count > 0)
                    {
                        var entry = _logQueue.Dequeue();
                        sw.WriteLine("{0}\t{1}", entry.LogTime, entry.Message);
                    }
                }
            }
        }

        internal class Log
        {
            /// <summary>
            /// Initializes a new instance of the <see cref="Log"/> class.
            /// </summary>
            /// <param name="message">The message.</param>
            public Log(string message)
            {
                Message = message;
                LogDate = DateTime.Now.ToString("yyyy-MM-dd");
                LogTime = DateTime.Now.ToString("hh:mm:ss.fff tt");
            }

            /// <summary>
            /// Gets or sets the message.
            /// </summary>
            /// <value>
            /// The message.
            /// </value>
            public string Message { get; set; }

            /// <summary>
            /// Gets or sets the log time.
            /// </summary>
            /// <value>
            /// The log time.
            /// </value>
            public string LogTime { get; set; }

            /// <summary>
            /// Gets or sets the log date.
            /// </summary>
            /// <value>
            /// The log date.
            /// </value>
            public string LogDate { get; set; }
        }
    }
}