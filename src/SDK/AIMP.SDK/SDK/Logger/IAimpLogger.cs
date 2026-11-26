using System;

namespace AIMP.SDK.Logger;

public interface IAimpLogger
{
    void Verbose(string message);

    void Verbose(string message, params object[] values);

    void Verbose(Exception? exception, string messageTemplate, params object[] values);

    void Information(string message);

    void Information(string message, params object[] values);

    void Information(Exception? exception, string messageTemplate, params object[] values);

    void Error(string message, params object[] values);

    void Error(Exception? exception, string messageTemplate, params object[] values);

    void Fatal(string message);

    void Fatal(string message, params object[] values);

    void Fatal(Exception? exception, string messageTemplate, params object[] values);

    void Debug(string message);

    void Debug(string message, params object[] values);

    void Debug(Exception? exception, string messageTemplate, params object[] values);
}