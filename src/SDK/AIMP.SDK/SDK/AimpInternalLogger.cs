using System;
using AIMP.Internal;
using AIMP.SDK.Logger;

namespace AIMP.SDK;

/// <summary>
/// Legacy SDK logger kept for source compatibility.
///
/// It now forwards to the same internal log sink as
/// <see cref="InternalLogger"/> and implements <see cref="IAimpLogger"/>.
/// New code should use <see cref="AimpLogging.Logger"/> or
/// <see cref="InternalLogger"/> instead.
/// </summary>
[Obsolete("Use AimpLogging.Logger or InternalLogger instead.")]
public class AimpInternalLogger : IAimpLogger, IDisposable
{
    private static readonly AimpInternalLogger Shared = new AimpInternalLogger();

    public static AimpInternalLogger Instance => Shared;

    public void LogMessage(string message)
    {
        Information(message);
    }

    public void Verbose(string message)
    {
        InternalLog.Instance.Verbose(message);
    }

    public void Verbose(string message, params object[] values)
    {
        InternalLog.Instance.Verbose(message, values);
    }

    public void Verbose(Exception exception, string messageTemplate, params object[] values)
    {
        InternalLog.Instance.Verbose(exception, messageTemplate, values);
    }

    public void Information(string message)
    {
        InternalLog.Instance.Information(message);
    }

    public void Information(string message, params object[] values)
    {
        InternalLog.Instance.Information(message, values);
    }

    public void Information(Exception exception, string messageTemplate, params object[] values)
    {
        InternalLog.Instance.Information(exception, messageTemplate, values);
    }

    public void Error(string message, params object[] values)
    {
        InternalLog.Instance.Error(message, values);
    }

    public void Error(Exception exception, string messageTemplate, params object[] values)
    {
        InternalLog.Instance.Error(exception, messageTemplate, values);
    }

    public void Fatal(string message)
    {
        InternalLog.Instance.Fatal(message);
    }

    public void Fatal(string message, params object[] values)
    {
        InternalLog.Instance.Fatal(message, values);
    }

    public void Fatal(Exception exception, string messageTemplate, params object[] values)
    {
        InternalLog.Instance.Fatal(exception, messageTemplate, values);
    }

    public void Debug(string message)
    {
        InternalLog.Instance.Debug(message);
    }

    public void Debug(string message, params object[] values)
    {
        InternalLog.Instance.Debug(message, values);
    }

    public void Debug(Exception exception, string messageTemplate, params object[] values)
    {
        InternalLog.Instance.Debug(exception, messageTemplate, values);
    }

    public void Dispose()
    {
    }
}