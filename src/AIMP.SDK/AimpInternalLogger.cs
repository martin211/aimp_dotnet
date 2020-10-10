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
using System.IO;
using System.Reflection;

namespace AIMP.SDK
{
    public class AimpInternalLogger : IAimpLogger, IDisposable
    {
        private StreamWriter _streamWriter;
        private static AimpInternalLogger _instance;

        public static AimpInternalLogger Instance => _instance ?? (_instance = new AimpInternalLogger());

        public AimpInternalLogger()
        {
            var logFilePath = Path.Combine(Path.GetPathRoot(Assembly.GetExecutingAssembly().Location), "aimp_dotnet.log");
            _streamWriter = new StreamWriter(logFilePath);
        }

        public void LogMessage(string message)
        {
            _streamWriter.WriteLine(message);
            _streamWriter.Flush();
        }

        public void Dispose()
        {
            _streamWriter?.Flush();
            _streamWriter?.Close();
            _streamWriter?.Dispose();
        }
    }
}
