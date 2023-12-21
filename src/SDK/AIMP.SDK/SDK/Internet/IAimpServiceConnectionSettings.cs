//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

namespace AIMP.SDK.Internet;

public enum ConnectionType
{
    Direct,
    Proxy,
    SystemDefaults
}

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