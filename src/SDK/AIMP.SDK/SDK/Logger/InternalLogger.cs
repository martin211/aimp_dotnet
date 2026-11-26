using System;
using AIMP.Internal;

namespace AIMP.SDK.Logger;

/// <summary>
/// Default public <see cref="IAimpLogger"/> implementation.
///
/// It forwards to <see cref="InternalLog"/>, which writes to
/// <see cref="System.Diagnostics.Debug"/> and to the SDK log file and does
/// not require any external logging package. A plugin may register its own
/// logger through <see cref="AimpLogging.Register"/> or by overriding
/// <see cref="AIMP.SDK.AimpPlugin.InitializeLogger"/>.
/// </summary>
public class InternalLogger : IAimpLogger
{
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
}
