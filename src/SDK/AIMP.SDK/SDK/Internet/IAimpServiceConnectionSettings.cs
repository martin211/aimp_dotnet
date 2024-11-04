//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Internet;

/// <summary>
/// The connection type enum
/// </summary>
public enum ConnectionType
{
    /// <summary>
    /// Direct connection
    /// </summary>
    Direct,
    /// <summary>
    /// Proxy connection
    /// </summary>
    Proxy,
    /// <summary>
    /// The system defaults connection
    /// </summary>
    SystemDefaults
}

/// <summary>
/// This service provides an access to current connection settings. 
/// </summary>
public interface IAimpServiceConnectionSettings
{
    /// <summary>
    /// Gets or sets the value of the connection type
    /// </summary>
    ConnectionType ConnectionType { get; set; }

    /// <summary>
    /// Gets or sets the symbolic or IP address of proxy-service. Only for Proxy connection type.
    /// </summary>
    string ProxyServer { get; set; }

    /// <summary>
    /// Gets or sets the port of proxy server. Only for Proxy connection type.
    /// </summary>
    string ProxyPort { get; set; }

    /// <summary>
    /// Gets or sets the User name (optional, can be empty). Only for Proxy connection type.
    /// </summary>
    string ProxyUserName { get; set; }

    /// <summary>
    /// Gets or sets the User password (optional, can be empty). Only for Proxy connection type.
    /// </summary>
    string ProxyUserPass { get; set; }

    /// <summary>
    /// Gets or sets the value of the Timeout, in milliseconds.
    /// </summary>
    int TimeOut { get; set; }

    /// <summary>
    /// Gets or sets the value of the user agent
    /// </summary>
    string UserAgent { get; set; }
}