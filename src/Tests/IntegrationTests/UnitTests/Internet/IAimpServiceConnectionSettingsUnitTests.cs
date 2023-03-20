//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using AIMP.SDK.Internet;

using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Internet;

[TestFixture(Category = "ServiceConnectionSettings")]
public class IAimpServiceConnectionSettingsUnitTests : AimpIntegrationTest
{
    [Test]
    public void ConnectionType_ShouldChange()
    {
        Player.ServiceConnectionSettings.ConnectionType = ConnectionType.Proxy;

        var actual = Player.ServiceConnectionSettings.ConnectionType;
        AimpAssert.AreEqual(ConnectionType.Proxy, actual);
    }

    [Test]
    public void ProxyServer_ShouldChange()
    {
        const string expected = "localhost";

        Player.ServiceConnectionSettings.ProxyServer = expected;

        var actual = Player.ServiceConnectionSettings.ProxyServer;

        AimpAssert.AreEqual(expected, actual);
    }

    [Test]
    public void ProxyPort_ShouldChange()
    {
        const string expected = "8888";

        Player.ServiceConnectionSettings.ProxyPort = expected;

        var actual = Player.ServiceConnectionSettings.ProxyPort;

        AimpAssert.AreEqual(expected, actual);
    }

    [Test]
    public void ProxyUserName_ShouldChange()
    {
        const string expected = "User";

        Player.ServiceConnectionSettings.ProxyUserName = expected;

        var actual = Player.ServiceConnectionSettings.ProxyUserName;

        AimpAssert.AreEqual(expected, actual);
    }

    [Test]
    public void ProxyUserPass_ShouldChange()
    {
        const string expected = "ProxyUserPass";

        Player.ServiceConnectionSettings.ProxyUserPass = expected;

        var actual = Player.ServiceConnectionSettings.ProxyUserPass;

        AimpAssert.AreEqual(expected, actual);
    }

    [Test]
    public void UserAgent_ShouldChange()
    {
        const string expected = "UserAgent";

        Player.ServiceConnectionSettings.UserAgent = expected;

        var actual = Player.ServiceConnectionSettings.UserAgent;

        AimpAssert.AreEqual(expected, actual);
    }

    [Test]
    public void TimeOut_ShouldChange()
    {
        const int expected = 20000;

        Player.ServiceConnectionSettings.TimeOut = expected;

        var actual = Player.ServiceConnectionSettings.TimeOut;

        AimpAssert.AreEqual(expected, actual);
    }
}