using System;
using AIMP.Logger;

namespace AIMP.DotNet.MusicLibrary
{
    [Serializable]
    public class Logger : MarshalByRefObject, IAimpLogger
    {
        public void Verbose(string message)
        {
            System.Diagnostics.Debug.WriteLine(message, "Verbose");
        }

        public void Verbose(string message, params object[] values)
        {
            System.Diagnostics.Debug.WriteLine(message, "Verbose");
        }

        public void Verbose(Exception exception, string messageTemplate, params object[] values)
        {
            var msg = $"{messageTemplate}. Error: {exception}";
            System.Diagnostics.Debug.WriteLine(msg, "Verbose");
        }

        public void Information(string message)
        {
            System.Diagnostics.Debug.WriteLine(message, "Information");
        }

        public void Information(string message, params object[] values)
        {
            System.Diagnostics.Debug.WriteLine(message, "Information");
        }

        public void Information(Exception exception, string messageTemplate, params object[] values)
        {
            var msg = $"{messageTemplate}. Error: {exception}";
            System.Diagnostics.Debug.WriteLine(msg, "Information");
        }

        public void Error(string message)
        {
            System.Diagnostics.Debug.WriteLine(message, "Error");
        }

        public void Error(string message, params object[] values)
        {
            System.Diagnostics.Debug.WriteLine(message, "Error");
        }

        public void Error(Exception exception, string messageTemplate, params object[] values)
        {
            var msg = $"{messageTemplate}. Error: {exception}";
            System.Diagnostics.Debug.WriteLine(msg, "Error");
        }

        public void Debug(string message)
        {
            System.Diagnostics.Debug.WriteLine(message, "Debug");
        }

        public void Debug(string message, params object[] values)
        {
            System.Diagnostics.Debug.WriteLine(message, "Debug");
        }

        public void Debug(Exception exception, string messageTemplate, params object[] values)
        {
            var msg = $"{messageTemplate}. Error: {exception}";
            System.Diagnostics.Debug.WriteLine(msg, "Debug");
        }

        public void Fatal(string message)
        {
            System.Diagnostics.Debug.WriteLine(message, "Fatal");
        }

        public void Fatal(string message, params object[] values)
        {
            System.Diagnostics.Debug.WriteLine(message, "Fatal");
        }

        public void Fatal(Exception exception, string messageTemplate, params object[] values)
        {
            var msg = $"{messageTemplate}. Error: {exception}";
            System.Diagnostics.Debug.WriteLine(msg, "Fatal");
        }
    }
}