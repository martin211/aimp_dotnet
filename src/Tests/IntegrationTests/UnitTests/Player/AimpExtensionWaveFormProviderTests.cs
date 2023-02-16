//  ----------------------------------------------------
//  AIMP DotNet SDK
// 
//  Copyright (c) 2014 - 2023 Evgeniy Bogdan
//  https://github.com/martin211/aimp_dotnet
// 
//  Mail: mail4evgeniy@gmail.com
//  ----------------------------------------------------

using System.Collections.Generic;
using AIMP.SDK;
using AIMP.SDK.Player.Extensions;
using AIMP.SDK.Player.Objects;
using AIMP.SDK.Threading;
using Aimp.TestRunner.TestFramework;
using NUnit.Framework;

namespace Aimp.TestRunner.UnitTests.Player;

public class AimpExtensionWaveFormProviderTests : AimpIntegrationTest
{
    public class AimpExtensionWaveFormProvider : IAimpExtensionWaveFormProvider
    {
        public AimpActionResult Calculate(string fileUri, IAimpTaskOwner owner, IList<IAimpWaveformPeakInfo> peaks)
        {
            return new AimpActionResult(ActionResultType.OK);
        }
    }

    private AimpExtensionWaveFormProvider _target;

    [Test]
    [Order(1)]
    public void ShouldRegisterExtension()
    {
        ExecuteInMainThread(() =>
        {
            _target = new AimpExtensionWaveFormProvider();
            var res = Player.Core.RegisterExtension(_target);

            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
        });
    }

    [Test]
    [Ignore("Not working")]
    public void ShouldUnregisterExtension()
    {
        ExecuteInMainThread(() =>
        {
            var res = Player.Core.UnregisterExtension(_target);
            AimpAssert.AreEqual(ActionResultType.OK, res.ResultType);
            _target = null;
        });
    }
}