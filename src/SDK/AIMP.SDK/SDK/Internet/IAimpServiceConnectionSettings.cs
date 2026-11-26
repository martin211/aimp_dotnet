namespace AIMP.SDK.Internet;

public interface IAimpServiceConnectionSettings
{
    ConnectionType ConnectionType { get; set; }

    string ProxyServer { get; set; }

    string ProxyPort { get; set; }

    string ProxyUserName { get; set; }

    string ProxyUserPass { get; set; }

    int TimeOut { get; set; }

    string UserAgent { get; set; }
}