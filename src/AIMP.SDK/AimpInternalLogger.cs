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
using AIMP.SDK.MessageDispatcher;
using AIMP.SDK.Player;

namespace AIMP.SDK
{
    public class AimpInternalLogger : IAimpLogger, IDisposable
    {
        private readonly IAimpPlayer _player;
        private StreamWriter _streamWriter;

        public AimpInternalLogger(IAimpPlayer player)
        {
            _player = player;
            var logFilePath = Path.Combine(player.Core.GetPath(AimpCorePathType.Profile), "aimp_dotnet.log");
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
