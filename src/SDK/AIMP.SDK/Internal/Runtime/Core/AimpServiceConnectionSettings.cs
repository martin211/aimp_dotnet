using System;
using AIMP.Internal.Native.Objects;
using AIMP.Internal.Runtime.Common;
using AIMP.SDK.Internet;

namespace AIMP.Internal.Runtime.Core;

/// <summary>
/// v1 <see cref="IAimpServiceConnectionSettings"/> (IAIMPPropertyList).
/// </summary>
internal sealed class AimpServiceConnectionSettings : AimpObjectWrapper, IAimpServiceConnectionSettings
{
    private readonly AimpPropertyBag _properties;

    public AimpServiceConnectionSettings(IntPtr borrowedPointer)
    {
        _properties = AimpPropertyBag.FromOwned(
            AimpComHelper.QueryInterface(borrowedPointer, AimpIids.IAIMPPropertyList));
    }

    public ConnectionType ConnectionType
    {
        get => (ConnectionType)(_properties?.GetInt32(AimpPropId.ConnectionType) ?? 0);
        set => _properties?.SetInt32(AimpPropId.ConnectionType, (int)value);
    }

    public string ProxyServer
    {
        get => _properties?.GetString(AimpPropId.ConnectionProxyServer);
        set => _properties?.SetString(AimpPropId.ConnectionProxyServer, value);
    }

    public string ProxyPort
    {
        get => _properties?.GetString(AimpPropId.ConnectionProxyPort);
        set => _properties?.SetString(AimpPropId.ConnectionProxyPort, value);
    }

    public string ProxyUserName
    {
        get => _properties?.GetString(AimpPropId.ConnectionProxyUserName);
        set => _properties?.SetString(AimpPropId.ConnectionProxyUserName, value);
    }

    public string ProxyUserPass
    {
        get => _properties?.GetString(AimpPropId.ConnectionProxyUserPass);
        set => _properties?.SetString(AimpPropId.ConnectionProxyUserPass, value);
    }

    public int TimeOut
    {
        get => _properties?.GetInt32(AimpPropId.ConnectionTimeout) ?? 0;
        set => _properties?.SetInt32(AimpPropId.ConnectionTimeout, value);
    }

    public string UserAgent
    {
        get => _properties?.GetString(AimpPropId.ConnectionUserAgent);
        set => _properties?.SetString(AimpPropId.ConnectionUserAgent, value);
    }

    protected override void OnDispose()
    {
        _properties?.Dispose();
    }
}